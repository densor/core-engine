#pragma once
#include "CLIMessageManager.h"
#include <hash_map>
#include <vector>

namespace nsCore
{

  class IMessageHandler;

  class BaseMessageManager : public IMessageManager
  {
  public:
    BaseMessageManager(void);
    virtual ~BaseMessageManager(void);

    virtual void HandleMessage(IMessage * message);
    virtual void RegisterMessageHandler(unsigned messageID, IMessageHandler* handler);
    virtual void UnregisterMessageHandler(unsigned messageID, IMessageHandler* handler);

  private:
    std::hash_map<unsigned, std::vector<IMessageHandler*> > handlers;
  };

} // namespace nsCore