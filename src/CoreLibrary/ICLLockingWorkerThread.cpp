#include "ICLLockingWorkerThread.h"
#include "ICLLockingTaskScheduler.h"
#include "CLIThreadTask.h"
#include <cassert>

namespace nsCore
{

  LockingWorkerThread::LockingWorkerThread(LockingTaskScheduler* taskScheduler, ThreadEnumeration type)
    : mScheduler(taskScheduler), mType(type), mRunning(true)
  {
    assert(taskScheduler != NULL && "Task scheduler pointer must be not NULL.");
    assert((TE_SHORT_TASK == type || TE_LONG_TASK == type) && "Thread type must be short or long.");
  }

  LockingWorkerThread::~LockingWorkerThread(void)
  {
    assert(!mRunning && "Worker thread must be stopped by calling End() before destruction.");
  }

  void LockingWorkerThread::ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type)
  {
    mScheduler->ScheduleTasks(tasks, type);
  }

  void LockingWorkerThread::Start(void)
  {
    while(mRunning)
    {
      IThreadTask* task = mScheduler->GetTask(mType);
      if(task != NULL)
      {
        task->Execute(this);
        mScheduler->Unblock(task, mType);
        task->Suicide();
      }
    }
  }

  void LockingWorkerThread::End(void)
  {
    mRunning = false;
  }

} // namespace nsCore