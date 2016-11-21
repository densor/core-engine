#pragma once

namespace nsCore
{

  class IMessage;
  class IMessageHandler;

  class IMessageManager
  {
  protected:
    virtual ~IMessageManager(void) {}
  public:
    virtual void HandleMessage(IMessage * message) = 0;
    virtual void RegisterMessageHandler(unsigned messageID, IMessageHandler* handler) = 0;
    virtual void UnregisterMessageHandler(unsigned messageID, IMessageHandler* handler) = 0;
  };

} // namespace nsCore