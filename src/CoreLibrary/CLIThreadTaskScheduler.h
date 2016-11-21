#pragma once
#include <vector>

namespace nsCore
{

  class IThreadTask;

  class IThreadTaskScheduler
  {
  public:
    enum ThreadEnumeration
    {
      TE_SHORT_TASK = 0,
      TE_LONG_TASK = 1
    };

      // schedule one or more tasks
      // type is an implementation defined value
    virtual void ScheduleTasks(std::vector<IThreadTask*> const & tasks, ThreadEnumeration type) = 0;

  protected:
    virtual ~IThreadTaskScheduler(void) {}
  };

} // namespace nsCore