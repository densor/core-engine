#include "ICLLocklessWorkerThread.h"
#include "ICLLocklessTaskScheduler.h"
#include "CLIThreadTask.h"
#include <cassert>

namespace nsCore
{

  static const unsigned THIS_MEMORY_FOOTPRINT = 256;
  const unsigned INTERNAL_TASK_ARRAY_SIZE_BYTES = THIS_MEMORY_FOOTPRINT - sizeof(LocklessWorkerThread) % THIS_MEMORY_FOOTPRINT;
  const unsigned short INTERNAL_TASK_ARRAY_SIZE_POINTERS = INTERNAL_TASK_ARRAY_SIZE_BYTES / sizeof(IThreadTask*);

  /*
  * to keep thread execution mostly in the same cache line(s), we utilize memory as follows:
  *
  * expected memory layout (not to scale):
  *
  * CCCCCCCCSSSSSSSSSSSSEEEEEEELLLL
  *
  * where C's are class memory, S's are short tasks, L's are long tasks, E's are empty
  * the this pointer will point to the start of the C's
  * this + 1 (pointer arithmetic) will point to the start of the S's
  * this + THIS_MEMORY_FOOTPRINT (byte arithmetic) will point to one past the end of the L's
  * S's grow towards the end
  * L's grow towards the start
  * overflow for both S's and L's occurs when E's are gone
  * THIS_MEMORY_FOOTPRINT should be equal to an integer multiple of the cache line size
  */



  void LocklessWorkerThread::ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type)
  {
    for(unsigned i = 0; i < tasks.size(); ++i)
    {
      if(TE_SHORT_TASK == type)
      {
        StoreShortTask(tasks[i]);
      }
      else
      {
        assert(TE_LONG_TASK == type && "Task type is not valid.");
        StoreLongTask(tasks[i]);
      }
    }
  }

  LocklessWorkerThread::LocklessWorkerThread(LocklessTaskScheduler* taskScheduler, ThreadEnumeration type)
    : mTaskScheduler(taskScheduler), mType(type), mLongOverflow(), mShortOverflow(), mTaskIndex(0), 
    mShortSize(0), mLongSize(0), mRunning(taskScheduler != NULL), mTaskWaiting(false)
  {
    assert(taskScheduler != NULL && "Task Scheduler pointer must be not NULL.");
  }

  LocklessWorkerThread::~LocklessWorkerThread(void)
  {
    // memory leak could occur if the thread is not allowed to end normally
    //   by not calling End()
    // otherwise, all tasks will be passed to another holder and that will be
    //   responsible for making sure they get cleaned up
  }

  void LocklessWorkerThread::StoreShortTask(IThreadTask * task)
  {
    assert(task != NULL && "Task pointer being scheduled must be not NULL.");
    if(mShortSize + mLongSize == INTERNAL_TASK_ARRAY_SIZE_POINTERS)
    {
      mShortOverflow.push_back(task);
    }
    else
    {
      GetTaskArrayPointer()[mShortSize] = task;
      mShortSize += 1;
    }
  }

  void LocklessWorkerThread::StoreLongTask(IThreadTask * task)
  {
    assert(task != NULL && "Task pointer being scheduled must be not NULL.");
    if(mShortSize + mLongSize == INTERNAL_TASK_ARRAY_SIZE_POINTERS)
    {
      mLongOverflow.push_back(task);
    }
    else
    {
      mLongSize += 1;
      GetTaskArrayPointer()[INTERNAL_TASK_ARRAY_SIZE_POINTERS - mLongSize] = task;
    }
  }

  IThreadTask** LocklessWorkerThread::GetTaskArrayPointer(void)
  {
    return reinterpret_cast<IThreadTask**>(this + 1);
  }

  void LocklessWorkerThread::Start(void)
  {
    while(mRunning)
    {
      IThreadTask* task = GetTask();
      if(task != NULL)
      {
        mTaskWaiting = false;
        task->Execute(this);
        // TODO: unblock tasks
        task->Suicide();
        MoveScheduledTasks();
      }
    }
  }

  void LocklessWorkerThread::End(void)
  {
    mRunning = false;
  }

  IThreadTask* LocklessWorkerThread::GetTask(void)
  {
    if(!mTaskWaiting)
    {
      mTaskIndex = mTaskScheduler->GetNextQueuePosition(mType);
      mTaskWaiting = true;
    }

    return mTaskScheduler->GetTaskAtPosition(mType, mTaskIndex);
  }

  void LocklessWorkerThread::MoveScheduledTasks(void)
  {
    IThreadTask** myTaskArray = GetTaskArrayPointer();
    IThreadTask** taskArray = NULL;
    const unsigned taskArraySize = mTaskScheduler->GetTaskArraySize();
    assert(taskArraySize != 0 && "Size of task arrays returned by scheduler must by greater than 0.");
    unsigned taskArrayEnd = taskArraySize;
    // copy short tasks over to scheduler from local memory
    for(unsigned short i = 0; i < mShortSize; ++i)
    {
      if(taskArrayEnd == taskArraySize)
      {
        taskArray = SaveAndGetTaskArray(taskArray, TE_SHORT_TASK);
        taskArrayEnd = 0;
      }

      taskArray[taskArrayEnd] = myTaskArray[i];
      assert(taskArray[taskArrayEnd] != NULL && "Short task TRAMPLED to invalid value.");
      taskArrayEnd += 1;
    }
    // copy short tasks over to scheduler from overflow memory
    for(unsigned i = 0; i < mShortOverflow.size(); ++i)
    {
      if(taskArrayEnd == taskArraySize)
      {
        taskArray = SaveAndGetTaskArray(taskArray, TE_SHORT_TASK);
        taskArrayEnd = 0;
      }

      taskArray[taskArrayEnd] = mShortOverflow[i];
      assert(taskArray[taskArrayEnd] != NULL && "Short Overflow task TRAMPLED to invalid value.");
      taskArrayEnd += 1;
    }

    if(taskArray != NULL) mTaskScheduler->SaveTaskArray(taskArray, TE_SHORT_TASK);
    taskArray = NULL;
    mShortSize = 0;
    mShortOverflow.clear();

    // copy long tasks over to scheduler from local memory
    taskArrayEnd = taskArraySize;
    for(unsigned short i = 0; i < mLongSize; ++i)
    {
      if(taskArrayEnd == taskArraySize)
      {
        taskArray = SaveAndGetTaskArray(taskArray, TE_LONG_TASK);
        taskArrayEnd = 0;
      }

      taskArray[taskArrayEnd] = myTaskArray[INTERNAL_TASK_ARRAY_SIZE_POINTERS - 1 - i];
      assert(taskArray[taskArrayEnd] != NULL && "Long task TRAMPLED to invalid value.");
      taskArrayEnd += 1;
    }
    // copy long tasks over to scheduler from overflow memory
    for(unsigned i = 0; i < mLongOverflow.size(); ++i)
    {
      if(taskArrayEnd == taskArraySize)
      {
        taskArray = SaveAndGetTaskArray(taskArray, TE_LONG_TASK);
        taskArrayEnd = 0;
      }

      taskArray[taskArrayEnd] = mLongOverflow[i];
      assert(taskArray[taskArrayEnd] != NULL && "Long Overflow task TRAMPLED to invalid value.");
      taskArrayEnd += 1;
    }

    if(taskArray != NULL) mTaskScheduler->SaveTaskArray(taskArray, TE_LONG_TASK);
    taskArray = NULL;
    mLongSize = 0;
    mLongOverflow.clear();
  }

  IThreadTask** LocklessWorkerThread::SaveAndGetTaskArray(IThreadTask** taskArray, ThreadEnumeration type)
  {
    if(taskArray != NULL) mTaskScheduler->SaveTaskArray(taskArray, type);
    taskArray = mTaskScheduler->GetTaskArray(type);
    assert(taskArray != NULL && "Task array returned from task scheduler must be not NULL.");
    return taskArray;
  }

} // namespace nsCore