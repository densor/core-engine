#pragma once

namespace nsCore
{

  class IMessage;

  class IMessageHandler
  {
  public:
    virtual ~IMessageHandler(void) {}
    virtual void HandleMessage(IMessage* message) = 0;
  };

  template<typename CLASS, void (CLASS::*FUNCTION)(IMessage*)>
  class TemplatedMessageHandler : public IMessageHandler
  {
  private:
    TemplatedMessageHandler<CLASS, FUNCTION>& operator=(TemplatedMessageHandler<CLASS, FUNCTION> const &);
    CLASS * const pointer;

  public:
    TemplatedMessageHandler(CLASS * object) : pointer(object) {}
    virtual ~TemplatedMessageHandler(void) {}
    virtual void HandleMessage(IMessage* message)
    {
      (this->pointer->*(FUNCTION))(message);
    }
  };

} // namespace nsCore