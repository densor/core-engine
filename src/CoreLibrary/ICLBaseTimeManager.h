#pragma once
#include "CLITimeManager.h"

namespace nsCore
{

  class BaseTimeManager : public ITimeManager
  {
  public:
    BaseTimeManager(void);
    virtual ~BaseTimeManager(void);
    virtual void CreateUpdateMessages(CoreSpaceUpdateMessage * activeUpdateMessage, CoreSpaceUpdateMessage * pausedUpdateMessage, unsigned elapsedRealTime, unsigned elapsedGameTime);

  private:
    unsigned mTimes[4];
  };

} // namespace nsCore