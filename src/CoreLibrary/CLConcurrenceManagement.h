#pragma once

namespace nsCore
{

  class ConcurrenceObject;

  ConcurrenceObject* CreateConcurrenceObject(void);
  void DeleteConcurrenceObject(ConcurrenceObject* object);

  class ConcurrenceScopeLock
  {
  private:
    ConcurrenceScopeLock& operator=(ConcurrenceScopeLock const &);
  public:
    ConcurrenceScopeLock(ConcurrenceObject* object);
    ~ConcurrenceScopeLock(void);

  private:
    ConcurrenceObject* const currentObject;
  };

} // namespace nsCore