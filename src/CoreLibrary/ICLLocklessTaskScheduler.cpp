#include "ICLLocklessTaskScheduler.h"
#include <intrin.h>
#include <cassert>

namespace nsCore
{

  long LocklessTaskScheduler::GetNextQueuePosition(IThreadTaskScheduler::ThreadEnumeration type)
  {
    return _InterlockedIncrement(mQueueStart + ConvertType(type));
  }

  IThreadTask* LocklessTaskScheduler::GetTaskAtPosition(IThreadTaskScheduler::ThreadEnumeration type, long position)
  {
    if(mQueueEnd[ConvertType(type)] - position > 0)
    {
      // TODO: get a task
    }
    else
    {
      ScheduleOrBlock();
    }
    // TODO: change return value
    return NULL;
  }

  unsigned LocklessTaskScheduler::GetTaskArraySize(void)
  {
    return mTaskArraySize;
  }

  IThreadTask** LocklessTaskScheduler::GetTaskArray(IThreadTaskScheduler::ThreadEnumeration type)
  {
    long pos = _InterlockedIncrement(mPendingTasksEnd + ConvertType(type));

    if(pos - mPendingTasksStart[ConvertType(type)] >= mPendingTasksCapacity[ConvertType(type)])
    {
      ScheduleOrBlock();
    }
    
    // TODO: null out the array, otherwise how do we know the number of items in the array?
    return mPendingTasks[ConvertType(type)][pos % mPendingTasksCapacity[ConvertType(type)]];
  }

  void LocklessTaskScheduler::SaveTaskArray(IThreadTask**, IThreadTaskScheduler::ThreadEnumeration)
  {
    // this doesn't need to do anything, I guess?
  }

  int LocklessTaskScheduler::ConvertType(IThreadTaskScheduler::ThreadEnumeration type) const
  {
    if(IThreadTaskScheduler::TE_SHORT_TASK == type)
    {
      return 0;
    }
    else
    {
      assert(IThreadTaskScheduler::TE_LONG_TASK == type && "Thread type does is not valid.");
      return 1;
    }
  }

  void LocklessTaskScheduler::ScheduleOrBlock(void)
  {
    // TODO: schedule or block until scheduling is done
  }

} // namespace nsCore