#pragma once

namespace nsCore
{

  class IMessageManager;

  class ISystem
  {
  public:
    virtual ~ISystem(void) {}
    virtual void OnRegister(IMessageManager * engine) = 0;
  };

} // namespace nsCore