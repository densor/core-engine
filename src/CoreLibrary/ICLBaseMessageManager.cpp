#include "ICLBaseMessageManager.h"
#include "CLIMessageHandler.h"
#include "CLIMessage.h"
#include <cassert>
#include <algorithm>

namespace nsCore
{

  BaseMessageManager::BaseMessageManager(void)
  {

  }

  BaseMessageManager::~BaseMessageManager(void)
  {

  }

  void BaseMessageManager::HandleMessage(IMessage * message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    auto it = handlers.find(message->GetMessageID());
    if(it != handlers.end())
    {
      for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
      {
        (*it2)->HandleMessage(message);
      }
    }
  }

  void BaseMessageManager::RegisterMessageHandler(unsigned messageID, IMessageHandler* handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
    assert(std::find(handlers[messageID].begin(), handlers[messageID].end(), handler) == handlers[messageID].end() && "Handler registered twice.");
    handlers[messageID].push_back(handler);
  }

  void BaseMessageManager::UnregisterMessageHandler(unsigned messageID, IMessageHandler* handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
    auto it = handlers.find(messageID);
    assert(it != handlers.end() && "Attempted to unregister unknown handler.");

    std::vector<IMessageHandler*>& specificHandlers = it->second;
    for(unsigned i = 0; i < specificHandlers.size(); ++i)
    {
      if(specificHandlers[i] == handler)
      {
        specificHandlers[i] = specificHandlers.back();
        specificHandlers.pop_back();
        return;
      }
    }
    assert(false && "Attempted to unregister unknown handler.");
  }

} // namespace nsCore