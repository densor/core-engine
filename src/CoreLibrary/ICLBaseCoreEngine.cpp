#include "ICLBaseCoreEngine.h"
#include "CLISystem.h"
#include "CLCoreMessages.h"
#include "CLMessageEnumeration.h"
#include "ICLGetTime.h"
#include "CLIMessageHandler.h"
#include "CLITimeManager.h"
#include <cassert>
#include <algorithm>

namespace nsCore
{

  BaseCoreEngine::BaseCoreEngine(unsigned numSpaces, unsigned numPositions, ITimeManager* timeManager)
    : running(true), spaces(numSpaces, numPositions), times(timeManager)
  {
    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleQuitMessage>(this));
    RegisterMessageHandler(nsMessageTypes::CoreQuit, myHandlers.back());
    
    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleSpaceRegister>(this));
    RegisterMessageHandler(nsMessageTypes::CoreSpaceRegister, myHandlers.back());
    
    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleSpaceUnregister>(this));
    RegisterMessageHandler(nsMessageTypes::CoreSpaceUnregister, myHandlers.back());
    
    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleSpaceActivate>(this));
    RegisterMessageHandler(nsMessageTypes::CoreSpaceActivate, myHandlers.back());

    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleSpaceDeactivate>(this));
    RegisterMessageHandler(nsMessageTypes::CoreSpaceDeactivate, myHandlers.back());

    myHandlers.push_back(new TemplatedMessageHandler<BaseCoreEngine, &BaseCoreEngine::HandleSpaceGetState>(this));
    RegisterMessageHandler(nsMessageTypes::CoreSpaceGetState, myHandlers.back());
  }

  BaseCoreEngine::~BaseCoreEngine(void)
  {
    for(auto it = systems.rbegin(); it != systems.rend(); ++it)
    {
      delete *it;
    }
    for(auto it = myHandlers.begin(); it != myHandlers.end(); ++it)
    {
      delete *it;
    }
  }

  void BaseCoreEngine::AddSystem(ISystem * system)
  {
    assert(system != 0 && "System pointer must be not NULL.");
    assert(std::find(systems.begin(), systems.end(), system) == systems.end() && "System added twice.");
    systems.push_back(system);
    system->OnRegister(this);
  }

  void BaseCoreEngine::Initialize(void)
  {
    CoreInitializeMessage msg;
    HandleMessage(&msg);
  }

  void BaseCoreEngine::Run(void)
  {
    unsigned lastTime = GetTimeFunction();
    while(running)
    {
      unsigned currentTime = GetTimeFunction();
      unsigned elapsedRealTime = currentTime - lastTime;
      unsigned elapsedGameTime = elapsedRealTime;
      lastTime = currentTime;

      if(elapsedGameTime > 1000) elapsedGameTime = 16; // clamp elapsed game time to a reasonable amount in the event of a breakpoint or other long pause
      CoreSpaceUpdateMessage activeUpdateMessage;
      CoreSpaceUpdateMessage pausedUpdateMessage;
      times->CreateUpdateMessages(&activeUpdateMessage, &pausedUpdateMessage, elapsedRealTime, elapsedGameTime);
      spaces.UpdateSpaces(&activeUpdateMessage, &pausedUpdateMessage);
    }
  }

  void BaseCoreEngine::HandleQuitMessage(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    running = false;
  }

  void BaseCoreEngine::HandleSpaceRegister(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreSpaceRegisterMessage*>(message) != 0 && "Message type does not match message.");
    CoreSpaceRegisterMessage* mine = static_cast<CoreSpaceRegisterMessage*>(message);
    spaces.Register(mine->spaceId, mine->spacePosition, mine->listener);
  }

  void BaseCoreEngine::HandleSpaceUnregister(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreSpaceUnregisterMessage*>(message) != 0 && "Message type does not match message.");
    CoreSpaceUnregisterMessage* mine = static_cast<CoreSpaceUnregisterMessage*>(message);
    spaces.Unregister(mine->spaceId, mine->spacePosition, mine->listener);
  }

  void BaseCoreEngine::HandleSpaceActivate(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreSpaceActivateMessage*>(message) != 0 && "Message type does not match message.");
    CoreSpaceActivateMessage* mine = static_cast<CoreSpaceActivateMessage*>(message);
    spaces.Activate(mine->spaceId);
  }

  void BaseCoreEngine::HandleSpaceDeactivate(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreSpaceDeactivateMessage*>(message) != 0 && "Message type does not match message.");
    CoreSpaceDeactivateMessage* mine = static_cast<CoreSpaceDeactivateMessage*>(message);
    spaces.Deactivate(mine->spaceId);
  }

  void BaseCoreEngine::HandleSpaceGetState(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreSpaceGetStateMessage*>(message) != 0 && "Message type does not match message.");
    CoreSpaceGetStateMessage* mine = static_cast<CoreSpaceGetStateMessage*>(message);
    spaces.GetStateOfSpace(mine->spaceId, mine->currentFrame, mine->nextFrame);
  }

} // namespace nsCore