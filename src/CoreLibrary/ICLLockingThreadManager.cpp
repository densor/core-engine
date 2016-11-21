#include "ICLLockingThreadManager.h"
#include "ICLLockingWorkerThread.h"
#include "CLIThreadTask.h"
#include <cassert>

namespace nsCore
{

  void * ThreadInvoke(void * pointer)
  {
    reinterpret_cast<LockingWorkerThread *>(pointer)->Start();
    return 0;
  }

  LockingThreadManager::LockingThreadManager(unsigned numThreads)
  {
    assert(numThreads > 0 && "Number of threads must be greater than 0.");
    mNumLongs = 1;
    mLongs = new LockingWorkerThread(&mScheduler, TE_LONG_TASK);
    mNumShorts = numThreads - 1;
    if(mNumShorts > 0)
    {
      mShorts = static_cast<LockingWorkerThread*>(malloc(mNumShorts * sizeof(LockingWorkerThread)));
    }
    else
    {
      mShorts = NULL;
    }
    mHandles = new HANDLE[numThreads];
    mHandles[0] = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadInvoke), reinterpret_cast<void *>(mLongs), 0, 0);
    for(unsigned i = 0; i < mNumShorts; ++i)
    {
      new (mShorts + i) LockingWorkerThread(&mScheduler, TE_SHORT_TASK);
      mHandles[i + 1] = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadInvoke), reinterpret_cast<void *>(mShorts + i), 0, 0);
    }
  }

  LockingThreadManager::~LockingThreadManager(void)
  {
    mLongs->End();
    for(unsigned i = 0; i < mNumShorts; ++i)
    {
      mShorts[i].End();
    }

    WaitForSingleObject(mHandles[0], INFINITE);
    for(unsigned i = 0; i < mNumShorts; ++i)
    {
      WaitForSingleObject(mHandles[i + 1], INFINITE);
      mShorts[i].~LockingWorkerThread();
    }

    delete [] mHandles;
    free(mShorts);
    delete mLongs;
  }

  void LockingThreadManager::Synchonize(unsigned blockId)
  {
    while(mScheduler.IsBlocked(blockId))
    {
      IThreadTask* task = mScheduler.GetTask(TE_SHORT_TASK);
      if(task != NULL)
      {
        task->Execute(this);
        mScheduler.Unblock(task, TE_SHORT_TASK);
        task->Suicide();
      }
    }
  }

  void LockingThreadManager::ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type)
  {
    mScheduler.ScheduleTasks(tasks, type);
  }

} // namespace nsCore