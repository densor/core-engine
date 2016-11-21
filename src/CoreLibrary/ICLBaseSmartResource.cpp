#include "CLIResource.h"
#include "ICLBaseSmartResource.h"
#include <cassert>

namespace nsCore
{

  BaseSmartResource::BaseSmartResource(void)
    : mAcquisitions(0), mResource(0)
  {
  }

  BaseSmartResource::~BaseSmartResource(void)
  {
    Overwrite(0);
  }

  void BaseSmartResource::Acquire(void)
  {
    ++mAcquisitions;
  }

  void BaseSmartResource::Release(void)
  {
    assert(mAcquisitions > 0 && "Smart resource released more than acquired.");
    --mAcquisitions;
  }

  IResource* BaseSmartResource::GetResource(void)
  {
    assert(mResource != 0 && "Smart resource being used without a resource.");
    return mResource;
  }

  bool BaseSmartResource::IsUnused(void)
  {
    return mAcquisitions == 0;
  }

  void BaseSmartResource::Overwrite(IResource* resource)
  {
    if(mResource)
    {
      mResource->Release();
      if(mResource->IsUnused())
      {
        mResource->Suicide();
      }
    }

    mResource = resource;
    if(mResource)
    {
      mResource->Acquire();
    }
  }

} // namespace nsCore