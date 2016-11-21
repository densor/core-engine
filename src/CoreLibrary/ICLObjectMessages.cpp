#include "CLObjectMessages.h"
#include "CLMessageEnumeration.h"
#include <cassert>

namespace nsCore
{

  CoreObjectRegisterComponentMessage::CoreObjectRegisterComponentMessage(IComponent* registeredComponent)
    : component(registeredComponent)
  {
    assert(registeredComponent != 0 && "Component pointer must be not NULL.");
  }

  CoreObjectRegisterComponentMessage::~CoreObjectRegisterComponentMessage(void)
  {
  }

  unsigned CoreObjectRegisterComponentMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectRegisterComponent;
  }

  CoreObjectSendMessageUpwardsMessage::CoreObjectSendMessageUpwardsMessage(IMessage* subMessage)
    : message(subMessage)
  {
    assert(subMessage != 0 && "Message pointer must be not NULL.");
  }

  CoreObjectSendMessageUpwardsMessage::~CoreObjectSendMessageUpwardsMessage(void)
  {
  }

  unsigned CoreObjectSendMessageUpwardsMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectSendMessageUpwards;
  }
  
  CoreObjectSendMessageDownwardsMessage::CoreObjectSendMessageDownwardsMessage(IMessage* subMessage)
    : message(subMessage)
  {
    assert(subMessage != 0 && "Message pointer must be not NULL.");
  }

  CoreObjectSendMessageDownwardsMessage::~CoreObjectSendMessageDownwardsMessage(void)
  {
  }

  unsigned CoreObjectSendMessageDownwardsMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectSendMessageDownwards;
  }
  
  CoreObjectGetRootObjectMessage::CoreObjectGetRootObjectMessage(void)
    : root(0)
  {
  }

  CoreObjectGetRootObjectMessage::~CoreObjectGetRootObjectMessage(void)
  {
  }

  unsigned CoreObjectGetRootObjectMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectGetRootObject;
  }

} // namespace nsCore