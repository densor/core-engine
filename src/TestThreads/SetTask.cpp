#include "SetTask.h"

namespace nsCore
{

  namespace nsTest
  {

    SetTaskInt::SetTaskInt(int * address, int value, std::vector<unsigned> const & blocked)
      : mAddress(address), mValue(value), mBlocked(blocked)
    {
    }

    SetTaskInt::~SetTaskInt(void)
    {
    }

    void SetTaskInt::Execute(IThreadTaskScheduler*)
    {
      if(mAddress)
      {
        *mAddress = mValue;
      }
    }

    void SetTaskInt::Suicide(void)
    {
    }

    std::vector<unsigned> const & SetTaskInt::GetBlocked(void)
    {
      return mBlocked;
    }

  } // namespace nsTest

} // namespace nsCore