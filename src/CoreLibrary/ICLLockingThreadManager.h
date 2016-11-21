#pragma once
#include "CLIThreadTaskScheduler.h"
#include "CLIThreadManager.h"
#include "ICLLockingTaskScheduler.h"
#include <Windows.h>

namespace nsCore
{

  class LockingWorkerThread;

  class LockingThreadManager : public IThreadManager, public IThreadTaskScheduler
  {
  public:
    LockingThreadManager(unsigned numThreads);
    virtual ~LockingThreadManager(void);

    virtual void Synchonize(unsigned blockId);
    virtual void ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type);

  private:
    LockingTaskScheduler mScheduler;
    unsigned mNumShorts;
    unsigned mNumLongs;
    LockingWorkerThread* mShorts;
    LockingWorkerThread* mLongs;
    HANDLE* mHandles;
  };

} // namespace nsCore