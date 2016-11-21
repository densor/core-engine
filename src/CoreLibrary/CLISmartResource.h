#pragma once

namespace nsCore
{

  class IResource;

  class ISmartResource
  {
  protected:
    virtual ~ISmartResource(void) {}
  public:
    virtual void Acquire(void) = 0;
    virtual void Release(void) = 0;
    virtual IResource* GetResource(void) = 0;
  };

} // namespace nsCore