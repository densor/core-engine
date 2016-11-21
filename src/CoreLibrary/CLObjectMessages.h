#pragma once
#include "CLIMessage.h"

namespace nsCore
{

  class IComponent;
  class IMessageManager;

  class CoreObjectRegisterComponentMessage : public IMessage
  {
  private:
    CoreObjectRegisterComponentMessage& operator=(CoreObjectRegisterComponentMessage const &);
  public:
    CoreObjectRegisterComponentMessage(IComponent* registeredComponent);
    virtual ~CoreObjectRegisterComponentMessage(void);
    virtual unsigned GetMessageID(void);

    IComponent* const component;
  };

  // the subMessage will be dispatched to all sibling components and all parent objects and their components
  class CoreObjectSendMessageUpwardsMessage : public IMessage
  {
  private:
    CoreObjectSendMessageUpwardsMessage& operator=(CoreObjectSendMessageUpwardsMessage const &);
  public:
    CoreObjectSendMessageUpwardsMessage(IMessage* subMessage);
    virtual ~CoreObjectSendMessageUpwardsMessage(void);
    virtual unsigned GetMessageID(void);

    IMessage* const message;
  };

  // the subMessage will be dispatched to all sibling components and all sub objects and their components
  class CoreObjectSendMessageDownwardsMessage : public IMessage
  {
  private:
    CoreObjectSendMessageDownwardsMessage& operator=(CoreObjectSendMessageDownwardsMessage const &);
  public:
    CoreObjectSendMessageDownwardsMessage(IMessage* subMessage);
    virtual ~CoreObjectSendMessageDownwardsMessage(void);
    virtual unsigned GetMessageID(void);

    IMessage* const message;
  };

  class CoreObjectGetRootObjectMessage : public IMessage
  {
  private:
    CoreObjectGetRootObjectMessage& operator=(CoreObjectGetRootObjectMessage const &);
  public:
    CoreObjectGetRootObjectMessage(void);
    virtual ~CoreObjectGetRootObjectMessage(void);
    virtual unsigned GetMessageID(void);

    IMessageManager* root;
  };

} // namespace nsCore