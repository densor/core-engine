#pragma once

namespace nsCore
{

  class IMessageManager;
  class ISerializerOut;
  class ISerializerIn;

  class IComponent
  {
  protected:
    virtual ~IComponent(void) {}
  public:
    virtual unsigned GetComponentType(void) = 0;
    virtual void OnRegister(IMessageManager* owner) = 0;
    virtual void SerializeOut(ISerializerOut* out) = 0;
    virtual void SerializeIn(ISerializerIn* in) = 0;
  };

} // namespace nsCore