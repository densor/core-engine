#pragma once
#include "CLIThreadTaskScheduler.h"

namespace nsCore
{

  class IThreadTask;

  class LocklessTaskScheduler
  {
  public:
    LocklessTaskScheduler(long ptCapShort, long ptCapLong, unsigned taSize, IThreadTask*** taArray);

    long GetNextQueuePosition(IThreadTaskScheduler::ThreadEnumeration type);
    IThreadTask* GetTaskAtPosition(IThreadTaskScheduler::ThreadEnumeration type, long position);

    unsigned GetTaskArraySize(void);
    IThreadTask** GetTaskArray(IThreadTaskScheduler::ThreadEnumeration type);
    void SaveTaskArray(IThreadTask** taskArray, IThreadTaskScheduler::ThreadEnumeration type);

  private:
    LocklessTaskScheduler& operator=(LocklessTaskScheduler const &);

    int ConvertType(IThreadTaskScheduler::ThreadEnumeration type) const;
    void ScheduleOrBlock(void);

    volatile long mQueueStart[2];
    volatile long mQueueEnd[2];
    
    volatile long mPendingTasksStart[2];
    volatile long mPendingTasksEnd[2];
    const long mPendingTasksCapacity[2];
    const unsigned mTaskArraySize;
    IThreadTask*** mPendingTasks[2];
  };

} // namespace nsCore