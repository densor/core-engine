#include "ICLComponentCollection.h"
#include "CLComponentEnumeration.h"
#include "CLObjectMessages.h"
#include "CLMessageEnumeration.h"
#include <cassert>

namespace nsCore
{

  ComponentCollection::ComponentCollection(void)
    : parent(0), rcHandler(this), smuHandler(this), smdHandler(this), grHandler(this)
  {
    RegisterMessageHandler(nsMessageTypes::CoreObjectRegisterComponent, &rcHandler);
    RegisterMessageHandler(nsMessageTypes::CoreObjectSendMessageUpwards, &smuHandler);
    RegisterMessageHandler(nsMessageTypes::CoreObjectGetRootObject, &grHandler);
  }

  ComponentCollection::~ComponentCollection(void)
  {

  }

  unsigned ComponentCollection::GetComponentType(void)
  {
    return nsComponentIds::ComponentCollection;
  }

  void ComponentCollection::OnRegister(IMessageManager* owner)
  {
    assert(parent == 0 && "Parent set twice.");
    assert(owner != 0 && "Owner must be not NULL.");
    parent = owner;

    owner->RegisterMessageHandler(nsMessageTypes::CoreObjectSendMessageDownwards, &smdHandler);
  }

  void ComponentCollection::SerializeOut(ISerializerOut*)
  {
  }

  void ComponentCollection::SerializeIn(ISerializerIn*)
  {
  }

  void ComponentCollection::HandleRegisterComponent(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectRegisterComponentMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectRegisterComponentMessage* mine = static_cast<CoreObjectRegisterComponentMessage*>(message);
    assert(mine->component != 0 && "Component pointer must be not NULL.");
    components.push_back(mine->component);
    mine->component->OnRegister(this);
  }

  void ComponentCollection::HandleSendMessageUpwards(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectSendMessageUpwardsMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectSendMessageUpwardsMessage* mine = static_cast<CoreObjectSendMessageUpwardsMessage*>(message);
    assert(mine->message != 0 && "SubMessage pointer must be not NULL.");
    HandleMessage(mine->message);
    if(parent)
    {
      parent->HandleMessage(message);
    }
  }

  void ComponentCollection::HandleSendMessageDownwards(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectSendMessageDownwardsMessage*>(message) != 0 && "Message type does not match message.");
    CoreObjectSendMessageDownwardsMessage* mine = static_cast<CoreObjectSendMessageDownwardsMessage*>(message);
    assert(mine->message != 0 && "SubMessage pointer must be not NULL.");
    HandleMessage(mine->message);
    HandleMessage(message); // this message came from the parent component, so send to any objects listening to this component
  }

  void ComponentCollection::HandleGetRoot(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreObjectGetRootObjectMessage*>(message) != 0 && "Message type does not match message.");
    if(parent)
    {
      parent->HandleMessage(message);
    }
    else
    {
      CoreObjectGetRootObjectMessage* mine = static_cast<CoreObjectGetRootObjectMessage*>(message);
      mine->root = this;
    }
  }

  std::vector<IComponent*>& ComponentCollection::GetSubComponents(void)
  {
    return components;
  }

} // namespace nsCore