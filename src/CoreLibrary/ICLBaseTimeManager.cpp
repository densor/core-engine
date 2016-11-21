#include "ICLBaseTimeManager.h"
#include "CLCoreMessages.h"
#include <cassert>

namespace nsCore
{

  BaseTimeManager::BaseTimeManager(void)
  {
  }

  BaseTimeManager::~BaseTimeManager(void)
  {
  }

  void BaseTimeManager::CreateUpdateMessages(CoreSpaceUpdateMessage * activeUpdateMessage, CoreSpaceUpdateMessage * pausedUpdateMessage, unsigned elapsedRealTime, unsigned elapsedGameTime)
  {
    assert(activeUpdateMessage != 0 && "Active update message pointer must be not NULL.");
    assert(pausedUpdateMessage != 0 && "Paused update message pointer must be not NULL.");
    activeUpdateMessage->elapsedTimes = mTimes;
    pausedUpdateMessage->elapsedTimes = mTimes + 2;
    mTimes[0] = mTimes[2] = elapsedRealTime;
    mTimes[1] = elapsedGameTime;
    mTimes[3] = 0;
  }

} // namespace nsCore