#pragma once
#include "CLISmartResource.h"

namespace nsCore
{

  class BaseSmartResource : public ISmartResource
  {
  public:
    BaseSmartResource(void);
    virtual ~BaseSmartResource(void);
    virtual void Acquire(void);
    virtual void Release(void);
    virtual IResource* GetResource(void);
    
    bool IsUnused(void);
    void Overwrite(IResource* resource);

  private:
    int mAcquisitions;
    IResource* mResource;
  };

} // namespace nsCore