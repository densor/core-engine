#pragma once
#include "CLIThreadTaskScheduler.h"

namespace nsCore
{

  class IThreadTask;
  class LockingTaskScheduler;

  class LockingWorkerThread : public IThreadTaskScheduler
  {
  public:
    LockingWorkerThread(LockingTaskScheduler* taskScheduler, ThreadEnumeration type);
    virtual ~LockingWorkerThread(void);
    virtual void ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type);

    void Start(void);
    void End(void);

  private:
    LockingTaskScheduler* mScheduler;
    ThreadEnumeration mType;
    volatile bool mRunning;
  };

} // namespace nsCore