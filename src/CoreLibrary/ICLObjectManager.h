#pragma once
#include "CLISystem.h"
#include "ICLComponentFactory.h"
#include "ICLPrototypeFactory.h"
#include "ICLComponentCollectionCreator.h"
#include <vector>

namespace nsCore
{
  class IMessage;
  class IMessageHandler;
  class IObject;
  class IThreadTaskScheduler;
  class ComponentCollection;

  class ObjectManager : public ISystem
  {
  public:
    ObjectManager(IThreadTaskScheduler* threads);
    virtual ~ObjectManager(void);
    virtual void OnRegister(IMessageManager* engine);
    
  private:
    void HandleRegisterComponent(IMessage* message);
    void HandleRegisterPrototype(IMessage* message);
    void HandleCreateObject(IMessage* message);
    void HandleDestroyObject(IMessage* message);
    void HandleUpdate(IMessage* message);

    ComponentFactory mComponentFactory;
    PrototypeFactory mPrototypeFactory;
    ComponentCollectionCreator mCCCreator;

    IMessageManager* mEngine;
    std::vector<IMessageHandler*> mHandlers;
    std::vector<ComponentCollection*> mDeadObjects;

    IThreadTaskScheduler* const mThreads;
  };

} // namespace nsCore