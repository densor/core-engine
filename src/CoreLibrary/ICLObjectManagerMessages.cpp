#include "CLObjectManagerMessages.h"
#include "CLMessageEnumeration.h"
#include <cassert>

namespace nsCore
{

  CoreObjectManagerRegisterComponentMessage::CoreObjectManagerRegisterComponentMessage(unsigned aType, IComponentCreator* aCreator)
    : type(aType), creator(aCreator)
  {
    assert(aCreator != 0 && "Component creator pointer must be not NULL.");
  }

  CoreObjectManagerRegisterComponentMessage::~CoreObjectManagerRegisterComponentMessage(void)
  {
  }

  unsigned CoreObjectManagerRegisterComponentMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectManagerRegisterComponent;
  }

  CoreObjectManagerRegisterPrototypeMessage::CoreObjectManagerRegisterPrototypeMessage(unsigned aType, IObjectPrototypePattern* aPattern)
    : type(aType), pattern(aPattern)
  {
    assert(pattern != 0 && "Pattern pointer must be not NULL.");
  }

  CoreObjectManagerRegisterPrototypeMessage::~CoreObjectManagerRegisterPrototypeMessage(void)
  {
  }

  unsigned CoreObjectManagerRegisterPrototypeMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectManagerRegisterPrototype;
  }
  
  CoreObjectManagerCreateObjectMessage::CoreObjectManagerCreateObjectMessage(unsigned aType)
    : type(aType), result(0)
  {
  }

  CoreObjectManagerCreateObjectMessage::~CoreObjectManagerCreateObjectMessage(void)
  {
  }

  unsigned CoreObjectManagerCreateObjectMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectManagerCreateObject;
  }
  
  CoreObjectManagerDestroyObjectMessage::CoreObjectManagerDestroyObjectMessage(IMessageManager* aObject)
    : object(aObject)
  {
    assert(object != 0 && "Object pointer must be not NULL.");
  }

  CoreObjectManagerDestroyObjectMessage::~CoreObjectManagerDestroyObjectMessage(void)
  {
  }

  unsigned CoreObjectManagerDestroyObjectMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreObjectManagerDestroyObject;
  }

} // namespace nsCore