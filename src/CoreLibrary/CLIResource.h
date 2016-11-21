#pragma once

namespace nsCore
{

  class IResource
  {
  protected:
    virtual ~IResource(void) {}
  public:
    virtual void Suicide(void) {delete this;}
    virtual void Acquire(void) = 0;
    virtual void Release(void) = 0;
    virtual bool IsUnused(void) = 0;
    virtual bool IsNull(void) = 0;
  };

} // namespace nsCore