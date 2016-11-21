#pragma once
#include "CLIEngine.h"
#include "ICLBaseMessageManager.h"
#include "ICLSpaceManager.h"
#include <vector>

namespace nsCore
{

  class ITimeManager;

  class BaseCoreEngine : public IEngine, public BaseMessageManager
  {
  public:
    BaseCoreEngine(unsigned numSpaces, unsigned numPositions, ITimeManager* timeManager);
    virtual ~BaseCoreEngine(void);
    virtual void AddSystem(ISystem * system);
    virtual void Initialize(void);
    virtual void Run(void);

    void HandleQuitMessage(IMessage* message);
    void HandleSpaceRegister(IMessage* message);
    void HandleSpaceUnregister(IMessage* message);
    void HandleSpaceActivate(IMessage* message);
    void HandleSpaceDeactivate(IMessage* message);
    void HandleSpaceGetState(IMessage* message);

  private:
    std::vector<ISystem*> systems;
    bool running;
    std::vector<IMessageHandler*> myHandlers;
    SpaceManager spaces;
    ITimeManager* times;
  };

} // namespace nsCore