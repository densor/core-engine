#pragma once
#include "CLIThreadTaskScheduler.h"
#include <queue>
#include <hash_map>

namespace nsCore
{

  class IThreadTask;
  class ConcurrenceObject;

  class LockingTaskScheduler
  {
  public:
    LockingTaskScheduler(void);
    ~LockingTaskScheduler(void);
    
    void ScheduleTasks(std::vector<IThreadTask*> const & tasks, IThreadTaskScheduler::ThreadEnumeration type);
    IThreadTask* GetTask(IThreadTaskScheduler::ThreadEnumeration type);
    void Unblock(IThreadTask* finishedTask, IThreadTaskScheduler::ThreadEnumeration type);
    bool IsBlocked(unsigned blockId);

  private:
    ConcurrenceObject* mCO;
    std::queue<IThreadTask*> mTasks[2];
    std::hash_map<unsigned, std::pair<unsigned, std::vector<IThreadTask*> > > mBlockedTasks[2];
  };

} // namespace nsCore