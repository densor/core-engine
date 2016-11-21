#pragma once
#include "CLIMessage.h"
#include "CLSpaces.h"

namespace nsCore
{

  class IMessageHandler;

  class CoreQuitMessage : public IMessage
  {
  private:
    CoreQuitMessage& operator=(CoreQuitMessage const &);
  public:
    CoreQuitMessage(void);
    virtual ~CoreQuitMessage(void);
    virtual unsigned GetMessageID(void);
  };

  class CoreInitializeMessage : public IMessage
  {
  private:
    CoreInitializeMessage& operator=(CoreInitializeMessage const &);
  public:
    CoreInitializeMessage(void);
    virtual ~CoreInitializeMessage(void);
    virtual unsigned GetMessageID(void);
  };

  class CoreFinalizeMessage : public IMessage
  {
  private:
    CoreFinalizeMessage& operator=(CoreFinalizeMessage const &);
  public:
    CoreFinalizeMessage(void);
    virtual ~CoreFinalizeMessage(void);
    virtual unsigned GetMessageID(void);
  };

  // Not thread-safe
  class CoreSpaceRegisterMessage : public IMessage
  {
  private:
    CoreSpaceRegisterMessage& operator=(CoreSpaceRegisterMessage const &);
  public:
    CoreSpaceRegisterMessage(unsigned id, unsigned position, IMessageHandler* handler);
    virtual ~CoreSpaceRegisterMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
    unsigned const spacePosition;
    IMessageHandler * const listener;
  };

  // Not thread-safe
  class CoreSpaceUnregisterMessage : public IMessage
  {
  private:
    CoreSpaceUnregisterMessage& operator=(CoreSpaceUnregisterMessage const &);
  public:
    CoreSpaceUnregisterMessage(unsigned id, unsigned position, IMessageHandler* handler);
    virtual ~CoreSpaceUnregisterMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
    unsigned const spacePosition;
    IMessageHandler * const listener;
  };

  // Not thread-safe
  class CoreSpaceActivateMessage : public IMessage
  {
  private:
    CoreSpaceActivateMessage& operator=(CoreSpaceActivateMessage const &);
  public:
    CoreSpaceActivateMessage(unsigned id);
    virtual ~CoreSpaceActivateMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
  };

  // Not thread-safe
  class CoreSpacePauseMessage : public IMessage
  {
  private:
    CoreSpacePauseMessage& operator=(CoreSpacePauseMessage const &);
  public:
    CoreSpacePauseMessage(unsigned id);
    virtual ~CoreSpacePauseMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
  };

  // Not thread-safe
  class CoreSpaceUnpauseMessage : public IMessage
  {
  private:
    CoreSpaceUnpauseMessage& operator=(CoreSpaceUnpauseMessage const &);
  public:
    CoreSpaceUnpauseMessage(unsigned id);
    virtual ~CoreSpaceUnpauseMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
  };

  // Not thread-safe
  class CoreSpaceTogglePauseMessage : public IMessage
  {
  private:
    CoreSpaceTogglePauseMessage& operator=(CoreSpaceTogglePauseMessage const &);
  public:
    CoreSpaceTogglePauseMessage(unsigned id);
    virtual ~CoreSpaceTogglePauseMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
  };

  // Not thread-safe
  class CoreSpaceDeactivateMessage : public IMessage
  {
  private:
    CoreSpaceDeactivateMessage& operator=(CoreSpaceDeactivateMessage const &);
  public:
    CoreSpaceDeactivateMessage(unsigned id);
    virtual ~CoreSpaceDeactivateMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
  };

  // Not thread-safe
  class CoreSpaceGetStateMessage : public IMessage
  {
  private:
    CoreSpaceGetStateMessage& operator=(CoreSpaceGetStateMessage const &);
  public:
    CoreSpaceGetStateMessage(unsigned id);
    virtual ~CoreSpaceGetStateMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const spaceId;
    nsSpaces::SpaceStates currentFrame;
    nsSpaces::SpaceStates nextFrame;
  };

  class CoreSpaceUpdateMessage : public IMessage
  {
  private:
    CoreSpaceUpdateMessage& operator=(CoreSpaceUpdateMessage const &);
  public:
    CoreSpaceUpdateMessage(void);
    virtual ~CoreSpaceUpdateMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned * elapsedTimes;
  };

} // namespace nsCore