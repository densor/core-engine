#pragma once
#include "CLISystem.h"
#include "ICLBaseFileManager.h"
#include <string>
#include <hash_map>
#include <vector>

namespace nsCore
{

  class IMessage;
  class IMessageHandler;
  class IResource;
  class BaseSmartResource;

  class BaseResourceManager : public ISystem
  {
  public:
    BaseResourceManager(void);
    virtual ~BaseResourceManager(void);
    virtual void OnRegister(IMessageManager * engine);
    
  private:
    void HandleStoreReader(IMessage* message);
    void HandleStoreWriter(IMessage* message);
    void HandleLoadResource(IMessage* message);
    void HandleGetResource(IMessage* message);
    void HandleStoreResource(IMessage* message);
    void HandleWriteResource(IMessage* message);
    void HandleUpdate(IMessage* message);

    BaseResourceManager& operator=(BaseResourceManager&);
    BaseResourceManager(BaseResourceManager&);

    void AllocateSmartResources(void);
    void DeallocateSmartResources(void);
    BaseSmartResource* ConstructSmartResource(IResource* resource);
    void DeconstructSmartResource(BaseSmartResource* smartResource);

    BaseFileManager mFileManager;
    
    std::hash_map<std::string, BaseSmartResource*> mResourceMap;
    std::hash_map<std::string, BaseSmartResource*>::iterator mDeallocationSearcher;
    std::vector<IMessageHandler*> mHandlers;
  };

} // namespace nsCore