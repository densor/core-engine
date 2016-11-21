#pragma once
#include <vector>
#include "CLIThreadTaskScheduler.h"

namespace nsCore
{

  class IThreadTask;
  class LocklessTaskScheduler;

  // This is a class that should not be extended. It does work based on 
  //   sizeof(*this) and thus extending it would likely cause trampling of 
  //   memory.
  class LocklessWorkerThread : public IThreadTaskScheduler
  {
  public:
    virtual void ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type);

  private:
    // private constructor to prevent inheritance
    LocklessWorkerThread(LocklessTaskScheduler* taskScheduler, ThreadEnumeration type);
    virtual ~LocklessWorkerThread(void);

    void StoreShortTask(IThreadTask* task);
    void StoreLongTask(IThreadTask* task);
    IThreadTask** GetTaskArrayPointer(void);
    void Start(void);
    void End(void);
    IThreadTask* GetTask(void);
    void MoveScheduledTasks(void);
    IThreadTask** SaveAndGetTaskArray(IThreadTask** taskArray, ThreadEnumeration type);

    LocklessTaskScheduler* mTaskScheduler;
    ThreadEnumeration mType;
    std::vector<IThreadTask*> mLongOverflow;
    std::vector<IThreadTask*> mShortOverflow;
    long mTaskIndex;
    unsigned short mShortSize;
    unsigned short mLongSize;
    volatile bool mRunning;
    bool mTaskWaiting;

    friend class LocklessThreadManager; // to allow it to create this class, since constructor is private
    static const unsigned INTERNAL_TASK_ARRAY_SIZE_BYTES;
    static const unsigned short INTERNAL_TASK_ARRAY_SIZE_POINTERS;
  };

} // namespace nsCore