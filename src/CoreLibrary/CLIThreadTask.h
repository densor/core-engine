#pragma once
#include <vector>

namespace nsCore
{

  class IThreadTaskScheduler;

  class IThreadTask
  {
  protected:
    virtual ~IThreadTask(void) {}
  public:
      // this will be called when your task is up for execution
      // when it returns, your task should be complete
    virtual void Execute(IThreadTaskScheduler* threadManager) = 0;

      // this will be called when the task is finished executing
      // override it to manage your own task deallocations
    virtual void Suicide(void) {delete this;}

	    // the value returned by this function is the type of task 
	    //   that blocks this one from running
    virtual unsigned GetBlocking(void) {return 0;}

	    // the value returned by this function is a list of types 
	    //   that belong to this task, used for determining what
      //   other tasks it blocks
    virtual std::vector<unsigned> const & GetBlocked(void) {return emptyBlocker;}

      // returns whether the task uses limited resources that need 
      //   managing
    virtual bool IsResourceTask(void) {return false;}

      // returns a list of resources that this task will use
    virtual std::vector<unsigned> const & GetResources(void) {return emptyBlocker;}

  private:
    static std::vector<unsigned> const emptyBlocker;
  };

} // namespace nsCore