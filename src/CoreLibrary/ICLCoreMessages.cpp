#include "CLCoreMessages.h"
#include "CLMessageEnumeration.h"
#include <cassert>

namespace nsCore
{

  CoreQuitMessage::CoreQuitMessage(void)
  {
  }

  CoreQuitMessage::~CoreQuitMessage(void)
  {
  }

  unsigned CoreQuitMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreQuit;
  }

  CoreInitializeMessage::CoreInitializeMessage(void)
  {
  }

  CoreInitializeMessage::~CoreInitializeMessage(void)
  {
  }

  unsigned CoreInitializeMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreInitialize;
  }

  CoreFinalizeMessage::CoreFinalizeMessage(void)
  {
  }

  CoreFinalizeMessage::~CoreFinalizeMessage(void)
  {
  }

  unsigned CoreFinalizeMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreFinalize;
  }

  CoreSpaceRegisterMessage::CoreSpaceRegisterMessage(unsigned id, unsigned position, IMessageHandler* handler)
    : spaceId(id), spacePosition(position), listener(handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
  }

  CoreSpaceRegisterMessage::~CoreSpaceRegisterMessage(void)
  {
  }

  unsigned CoreSpaceRegisterMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceRegister;
  }

  CoreSpaceUnregisterMessage::CoreSpaceUnregisterMessage(unsigned id, unsigned position, IMessageHandler* handler)
    : spaceId(id), spacePosition(position), listener(handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
  }

  CoreSpaceUnregisterMessage::~CoreSpaceUnregisterMessage(void)
  {
  }

  unsigned CoreSpaceUnregisterMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceUnregister;
  }

  CoreSpaceActivateMessage::CoreSpaceActivateMessage(unsigned id)
    : spaceId(id)
  {
  }

  CoreSpaceActivateMessage::~CoreSpaceActivateMessage(void)
  {
  }

  unsigned CoreSpaceActivateMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceActivate;
  }

  CoreSpacePauseMessage::CoreSpacePauseMessage(unsigned id)
    : spaceId(id)
  {
  }

  CoreSpacePauseMessage::~CoreSpacePauseMessage(void)
  {
  }

  unsigned CoreSpacePauseMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpacePause;
  }

  CoreSpaceUnpauseMessage::CoreSpaceUnpauseMessage(unsigned id)
    : spaceId(id)
  {
  }

  CoreSpaceUnpauseMessage::~CoreSpaceUnpauseMessage(void)
  {
  }

  unsigned CoreSpaceUnpauseMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceUnpause;
  }

  CoreSpaceTogglePauseMessage::CoreSpaceTogglePauseMessage(unsigned id)
    : spaceId(id)
  {
  }

  CoreSpaceTogglePauseMessage::~CoreSpaceTogglePauseMessage(void)
  {
  }

  unsigned CoreSpaceTogglePauseMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceTogglePause;
  }

  CoreSpaceDeactivateMessage::CoreSpaceDeactivateMessage(unsigned id)
    : spaceId(id)
  {
  }

  CoreSpaceDeactivateMessage::~CoreSpaceDeactivateMessage(void)
  {
  }

  unsigned CoreSpaceDeactivateMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceDeactivate;
  }

  CoreSpaceGetStateMessage::CoreSpaceGetStateMessage(unsigned id)
    : spaceId(id), currentFrame(nsSpaces::UnknownSpace), nextFrame(nsSpaces::UnknownSpace)
  {
  }

  CoreSpaceGetStateMessage::~CoreSpaceGetStateMessage(void)
  {
  }

  unsigned CoreSpaceGetStateMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceGetState;
  }

  CoreSpaceUpdateMessage::CoreSpaceUpdateMessage(void)
    : elapsedTimes(0)
  {
  }

  CoreSpaceUpdateMessage::~CoreSpaceUpdateMessage(void)
  {
  }

  unsigned CoreSpaceUpdateMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreSpaceUpdate;
  }

} // namespace nsCore