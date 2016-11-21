#include "ICLLockingTaskScheduler.h"
#include "CLConcurrenceManagement.h"
#include "CLIThreadTask.h"
#include <cassert>

namespace nsCore
{

  LockingTaskScheduler::LockingTaskScheduler(void)
  {
    mCO = CreateConcurrenceObject();
  }

  LockingTaskScheduler::~LockingTaskScheduler(void)
  {
    DeleteConcurrenceObject(mCO);
  }

  void LockingTaskScheduler::ScheduleTasks(std::vector<IThreadTask*> const & tasks, IThreadTaskScheduler::ThreadEnumeration type)
  {
    ConcurrenceScopeLock lock(mCO);
    for(unsigned i = 0; i < tasks.size(); ++i)
    {
      assert(tasks[i] != NULL && "Tasks being scheduled must be not NULL.");
      std::vector<unsigned> const & blocks = tasks[i]->GetBlocked();
      for(unsigned j = 0; j < blocks.size(); ++j)
      {
        auto it = mBlockedTasks[type].find(blocks[j]);
        if(it == mBlockedTasks[type].end())
        {
          mBlockedTasks[type][blocks[j]] = std::make_pair(1, std::vector<IThreadTask*>());
        }
        else
        {
          it->second.first += 1;
        }
      }

      auto it = mBlockedTasks[type].find(tasks[i]->GetBlocking());
      if(it != mBlockedTasks[type].end())
      {
        it->second.second.push_back(tasks[i]);
      }
      else
      {
        mTasks[type].push(tasks[i]);
      }
    }
  }

  IThreadTask* LockingTaskScheduler::GetTask(IThreadTaskScheduler::ThreadEnumeration type)
  {
    ConcurrenceScopeLock lock(mCO);
    IThreadTask* task = NULL;
    if(mTasks[type].size() > 0)
    {
      task = mTasks[type].front();
      mTasks[type].pop();
    }
    return task;
  }

  void LockingTaskScheduler::Unblock(IThreadTask* finishedTask, IThreadTaskScheduler::ThreadEnumeration type)
  {
    ConcurrenceScopeLock lock(mCO);
    std::vector<unsigned> const & blocks = finishedTask->GetBlocked();
    for(unsigned i = 0; i < blocks.size(); ++i)
    {
      auto it = mBlockedTasks[type].find(blocks[i]);
      assert(it != mBlockedTasks[type].end() && "Task block removed before blocking task was finished.");
      if(it->second.first == 1)
      {
        std::vector<IThreadTask*> const & tasks = it->second.second;
        for(unsigned j = 0; j < tasks.size(); ++j)
        {
          mTasks[type].push(tasks[j]);
        }
        mBlockedTasks[type].erase(blocks[i]);
      }
      else
      {
        it->second.first -= 1;
      }
    }
  }

  bool LockingTaskScheduler::IsBlocked(unsigned blockId)
  {
    ConcurrenceScopeLock lock(mCO);
    return mBlockedTasks[IThreadTaskScheduler::TE_SHORT_TASK].find(blockId) != mBlockedTasks[IThreadTaskScheduler::TE_SHORT_TASK].end();
  }

} // namespace nsCore