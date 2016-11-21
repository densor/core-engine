#include "ICLBaseResourceManager.h"
#include "ICLBaseSmartResource.h"
#include "CLCoreMessages.h"
#include "CLResourceMessages.h"
#include "CLIMessageHandler.h"
#include "CLMessageEnumeration.h"
#include "CLIMessageManager.h"
#include "CLSpaces.h"
#include <cassert>

namespace nsCore
{

  BaseResourceManager::BaseResourceManager(void)
  {
    AllocateSmartResources();
  }

  BaseResourceManager::~BaseResourceManager(void)
  {
    DeallocateSmartResources();
    for(auto it = mHandlers.begin(); it != mHandlers.end(); ++it)
    {
      delete *it;
    }
  }

  void BaseResourceManager::OnRegister(IMessageManager * engine)
  {
    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleStoreReader>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceStoreReader, mHandlers.back());
      
    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleStoreWriter>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceStoreWriter, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleLoadResource>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceLoad, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleGetResource>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceGet, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleStoreResource>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceStore, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleWriteResource>(this));
    engine->RegisterMessageHandler(nsMessageTypes::CoreResourceWrite, mHandlers.back());

    mHandlers.push_back(new TemplatedMessageHandler<BaseResourceManager, &BaseResourceManager::HandleUpdate>(this));
    CoreSpaceRegisterMessage msg(nsSpaces::RealTimeSpace, 0, mHandlers.back());
  }

  void BaseResourceManager::HandleStoreReader(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceStoreReaderMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceStoreReaderMessage* mine = static_cast<CoreResourceStoreReaderMessage*>(message);
    mFileManager.Store(mine->type, mine->reader);
  }

  void BaseResourceManager::HandleStoreWriter(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceStoreWriterMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceStoreWriterMessage* mine = static_cast<CoreResourceStoreWriterMessage*>(message);
    mFileManager.Store(mine->type, mine->writer);
  }

  void BaseResourceManager::HandleLoadResource(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceLoadMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceLoadMessage* mine = static_cast<CoreResourceLoadMessage*>(message);
    assert(mine->name != "" && "Resource name must be not empty.");
    assert(mine->path != "" && "Resource path must be not empty.");
    IResource* resource = mFileManager.ReadResource(mine->type, mine->path);
    if(resource != 0)
    {
      if(mResourceMap[mine->name] != 0)
      {
        mResourceMap[mine->name]->Overwrite(resource);
      }
      else
      {
        mResourceMap[mine->name] = ConstructSmartResource(resource);
      }
      mDeallocationSearcher = mResourceMap.begin();
    }
  }

  void BaseResourceManager::HandleGetResource(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceGetMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceGetMessage* mine = static_cast<CoreResourceGetMessage*>(message);
    assert(mine->name != "" && "Resource name must be not empty.");
    auto it = mResourceMap.find(mine->name);
    if(it != mResourceMap.end())
    {
      assert(it->second != 0 && "Resource TRAMPLED to invalid value.");
      mine->resource = it->second;
    }
  }

  void BaseResourceManager::HandleStoreResource(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceStoreMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceStoreMessage* mine = static_cast<CoreResourceStoreMessage*>(message);
    assert(mine->name != "" && "Resource name must be not empty.");
    assert(mine->resource != 0 && "Resource pointer must be not NULL.");
    if(mResourceMap[mine->name] != 0)
    {
      mResourceMap[mine->name]->Overwrite(mine->resource);
    }
    else
    {
      mResourceMap[mine->name] = ConstructSmartResource(mine->resource);
    }
    mDeallocationSearcher = mResourceMap.begin();
  }

  void BaseResourceManager::HandleWriteResource(IMessage* message)
  {
    assert(message != 0 && "Message pointer must be not NULL.");
    assert(dynamic_cast<CoreResourceWriteMessage*>(message) != 0 && "Message type does not match message.");
    CoreResourceWriteMessage* mine = static_cast<CoreResourceWriteMessage*>(message);
    assert(mine->path != "" && "Resource path must be not empty.");
    assert(mine->resource != 0 && "Resource pointer must be not NULL.");
    mFileManager.WriteResource(mine->type, mine->path, mine->resource);
  }

  void BaseResourceManager::HandleUpdate(IMessage*)
  {
    if(mDeallocationSearcher != mResourceMap.end())
    {
      if(mDeallocationSearcher->second && mDeallocationSearcher->second->IsUnused())
      {
        DeconstructSmartResource(mDeallocationSearcher->second);
        mDeallocationSearcher = mResourceMap.erase(mDeallocationSearcher);
      }
      else
      {
        ++mDeallocationSearcher;
      }
    }
    else
    {
      mDeallocationSearcher = mResourceMap.begin();
    }
  }

  void BaseResourceManager::AllocateSmartResources(void)
  {
    // TODO: object pool?
  }

  void BaseResourceManager::DeallocateSmartResources(void)
  {
    // TODO: modify this to match allocation method
    for(auto it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
    {
      DeconstructSmartResource(it->second);
    }
  }

  BaseSmartResource* BaseResourceManager::ConstructSmartResource(IResource* resource)
  {
    // TODO: modify this to match allocation method
    BaseSmartResource* smartResource = new BaseSmartResource();
    smartResource->Overwrite(resource);
    return smartResource;
  }

  void BaseResourceManager::DeconstructSmartResource(BaseSmartResource* smartResource)
  {
    // TODO: modify this to match allocation method
    delete smartResource;
  }

} // namespace nsCore