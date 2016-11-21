#include "CLConcurrenceManagement.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cassert>

namespace nsCore
{

  class ConcurrenceObject
  {
  private:
    CRITICAL_SECTION cs;

  public:
    ConcurrenceObject(void)
    {
      InitializeCriticalSection(&cs);
    }

    ~ConcurrenceObject(void)
    {
      DeleteCriticalSection(&cs);
    }

    void Lock(void)
    {
      EnterCriticalSection(&cs);
    }

    void Unlock(void)
    {
      LeaveCriticalSection(&cs);
    }
  };

  ConcurrenceObject* CreateConcurrenceObject(void)
  {
    return new ConcurrenceObject();
  }

  void DeleteConcurrenceObject(ConcurrenceObject* object)
  {
    assert(object != 0 && "ConcurrenceObject pointer must be not NULL.");
    delete object;
  }

  ConcurrenceScopeLock::ConcurrenceScopeLock(ConcurrenceObject* object)
    : currentObject(object)
  {
    assert(object != 0 && "ConcurrenceObject pointer must be not NULL.");
    currentObject->Lock();
  }

  ConcurrenceScopeLock::~ConcurrenceScopeLock(void)
  {
    assert(currentObject != 0 && "ConcurrenceScopeLock TRAMPLED to invalid state.");
    currentObject->Unlock();
  }

} // namespace nsCore
