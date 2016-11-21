#pragma once
#include "CLIComponent.h"
#include "ICLBaseMessageManager.h"
#include "CLIMessageHandler.h"

namespace nsCore
{

  class ComponentCollection : public IComponent, public BaseMessageManager
  {
  public:
    ComponentCollection(void);
    virtual ~ComponentCollection(void);
    virtual unsigned GetComponentType(void);
    virtual void OnRegister(IMessageManager* owner);
    virtual void SerializeOut(ISerializerOut* out);
    virtual void SerializeIn(ISerializerIn* in);

    void HandleRegisterComponent(IMessage* message);
    void HandleSendMessageUpwards(IMessage* message);
    void HandleSendMessageDownwards(IMessage* message);
    void HandleGetRoot(IMessage* message);

    std::vector<IComponent*>& GetSubComponents(void);

  private:
    IMessageManager* parent;
    std::vector<IComponent*> components;

    TemplatedMessageHandler<ComponentCollection, &ComponentCollection::HandleRegisterComponent> rcHandler;
    TemplatedMessageHandler<ComponentCollection, &ComponentCollection::HandleSendMessageUpwards> smuHandler;
    TemplatedMessageHandler<ComponentCollection, &ComponentCollection::HandleSendMessageDownwards> smdHandler;
    TemplatedMessageHandler<ComponentCollection, &ComponentCollection::HandleGetRoot> grHandler;
  };

} // namespace nsCore