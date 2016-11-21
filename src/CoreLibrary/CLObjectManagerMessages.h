#pragma once
#include "CLIMessage.h"

namespace nsCore
{

  class IMessageManager;
  class IComponentCreator;
  class IObjectPrototypePattern;

  class CoreObjectManagerRegisterComponentMessage : public IMessage
  {
  private:
    CoreObjectManagerRegisterComponentMessage& operator=(CoreObjectManagerRegisterComponentMessage const &);
  public:
    CoreObjectManagerRegisterComponentMessage(unsigned aType, IComponentCreator* aCreator);
    virtual ~CoreObjectManagerRegisterComponentMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const type;
    IComponentCreator* const creator;
  };

  class CoreObjectManagerRegisterPrototypeMessage : public IMessage
  {
  private:
    CoreObjectManagerRegisterPrototypeMessage& operator=(CoreObjectManagerRegisterPrototypeMessage const &);
  public:
    CoreObjectManagerRegisterPrototypeMessage(unsigned aType, IObjectPrototypePattern* aPattern);
    virtual ~CoreObjectManagerRegisterPrototypeMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const type;
    IObjectPrototypePattern* const pattern;
  };

  class CoreObjectManagerCreateObjectMessage : public IMessage
  {
  private:
    CoreObjectManagerCreateObjectMessage& operator=(CoreObjectManagerCreateObjectMessage const &);
  public:
    CoreObjectManagerCreateObjectMessage(unsigned aType);
    virtual ~CoreObjectManagerCreateObjectMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const type;
    IMessageManager* result;
  };

  class CoreObjectManagerDestroyObjectMessage : public IMessage
  {
  private:
    CoreObjectManagerDestroyObjectMessage& operator=(CoreObjectManagerDestroyObjectMessage const &);
  public:
    CoreObjectManagerDestroyObjectMessage(IMessageManager* aObject);
    virtual ~CoreObjectManagerDestroyObjectMessage(void);
    virtual unsigned GetMessageID(void);

    IMessageManager* object;
  };

} // namespace nsCore