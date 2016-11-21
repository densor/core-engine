#include "ICLObjectManager.h"
#include "ICLComponentFactory.h"
#include "ICLPrototypeFactory.h"
#include "ICLComponentCollection.h"
#include "CLObjectManagerMessages.h"
#include "CLObjectMessages.h"
#include "CLIMessageHandler.h"
#include "CLMessageEnumeration.h"
#include "CLIMessageManager.h"
#include "CLComponentEnumeration.h"
#include "CLIMessageManager.h"
#include "CLIComponent.h"
#include "CLCoreMessages.h"
#include "CLSpaces.h"
#include <cassert>

namespace nsCore
{

  ObjectManager::ObjectManager(IThreadTaskScheduler* threads)
    : mEngine(0), mComponentFactory(), mPrototypeFactory(&mComponentFactory), mCCCreator(&mComponentFactory), mThreads(threads)
  {
    mComponentFactory.RegisterComponentCreator(nsComponentIds::ComponentCollection, &mCCCreator);
  }

  ObjectManager::~ObjectManager(void)
  {
    for(auto it = mHandlers.begin(); it != mHandlers.end(); ++it)
    {
      delete *it;
    }
  }

  void ObjectManager::OnRegister(IMessageManager* engine)
  {
    assert(engine != 0 && "Engine pointer must be not NULL.");
    mEngine = engine;

    mHandlers.push_back(new TemplatedMessageHandler<ObjectManager, &ObjectManager::HandleRegisterComponent>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreObjectManagerRegisterComponent, mHandlers.back());
    
    mHandlers.push_back(new TemplatedMessageHandler<ObjectManager, &ObjectManager::HandleRegisterPrototype>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreObjectManagerRegisterPrototype, mHandlers.back());
    
    mHandlers.push_back(new TemplatedMessageHandler<ObjectManager, &ObjectManager::HandleCreateObject>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreObjectManagerCreateObject, mHandlers.back());
    
    mHandlers.push_back(new TemplatedMessageHandler<ObjectManager, &ObjectManager::HandleDestroyObject>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreObjectManagerDestroyObject, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<ObjectManager, &ObjectManager::HandleUpdate>(this));
    CoreSpaceRegisterMessage msg(nsSpaces::RealTimeSpace, 0, mHandlers.back());
  }

  void ObjectManager::HandleRegisterComponent(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectManagerRegisterComponentMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectManagerRegisterComponentMessage* mine = static_cast<CoreObjectManagerRegisterComponentMessage*>(message);
    mComponentFactory.RegisterComponentCreator(mine->type, mine->creator);
  }

  void ObjectManager::HandleRegisterPrototype(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectManagerRegisterPrototypeMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectManagerRegisterPrototypeMessage* mine = static_cast<CoreObjectManagerRegisterPrototypeMessage*>(message);
    mPrototypeFactory.RegisterPrototypePattern(mine->type, mine->pattern);
  }

  void ObjectManager::HandleCreateObject(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectManagerCreateObjectMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectManagerCreateObjectMessage* mine = static_cast<CoreObjectManagerCreateObjectMessage*>(message);
    mine->result = static_cast<ComponentCollection*>(mComponentFactory.CreateComponent(nsCore::nsComponentIds::ComponentCollection));
    mPrototypeFactory.CreatePrototype(mine->type, static_cast<ComponentCollection*>(mine->result));
  }

  void ObjectManager::HandleDestroyObject(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectManagerDestroyObjectMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectManagerDestroyObjectMessage* mine = static_cast<CoreObjectManagerDestroyObjectMessage*>(message);
    assert(mine->object != 0 && "Object pointer must be not NULL.");
    IMessageManager* object = mine->object;
    mine->object = 0;
    CoreObjectGetRootObjectMessage msg;
    object->HandleMessage(&msg);
    object = msg.root;
    assert(dynamic_cast<ComponentCollection*>(object) != 0 && "Object type is not expected ComponentCollection.");
    mDeadObjects.push_back(static_cast<ComponentCollection*>(object));
  }

  void ObjectManager::HandleUpdate(IMessage*)
  {
    // TODO: create threaded tasks for this
    for(auto it = mDeadObjects.begin(); it != mDeadObjects.end(); ++it)
    {
      mComponentFactory.DestroyComponent(*it);
    }
    mDeadObjects.clear();
  }

} // namespace nsCore