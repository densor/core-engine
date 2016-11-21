#pragma once

namespace nsCore
{

  class CoreSpaceUpdateMessage;

  class ITimeManager
  {
  protected:
    virtual ~ITimeManager(void) = 0;
  public:
    virtual void CreateUpdateMessages(CoreSpaceUpdateMessage * activeUpdateMessage, CoreSpaceUpdateMessage * pausedUpdateMessage, unsigned elapsedRealTime, unsigned elapsedGameTime) = 0;
  };

} // namespace nsCore