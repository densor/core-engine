#include "ICLGetTime.h"
#include <Windows.h>

namespace nsCore
{

  unsigned GetTimeFunction(void)
  {
    return timeGetTime();
  }

} // namespace nsCore