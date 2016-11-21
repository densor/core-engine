#include "CLResourceMessages.h"
#include "CLMessageEnumeration.h"
#include <cassert>

namespace nsCore
{

  CoreResourceStoreReaderMessage::CoreResourceStoreReaderMessage(unsigned resourceType, IResourceReader* resourceReader)
    : type(resourceType), reader(resourceReader)
  {
    assert(resourceReader != 0 && "Resource reader pointer must be not NULL.");
  }

  CoreResourceStoreReaderMessage::~CoreResourceStoreReaderMessage(void)
  {
  }

  unsigned CoreResourceStoreReaderMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceStoreReader;
  }

  CoreResourceStoreWriterMessage::CoreResourceStoreWriterMessage(unsigned resourceType, IResourceWriter* resourceWriter)
    : type(resourceType), writer(resourceWriter)
  {
    assert(resourceWriter != 0 && "Resource writer pointer must be not NULL.");
  }

  CoreResourceStoreWriterMessage::~CoreResourceStoreWriterMessage(void)
  {
  }

  unsigned CoreResourceStoreWriterMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceStoreWriter;
  }

  CoreResourceLoadMessage::CoreResourceLoadMessage(std::string const & resourcePath, std::string const & resourceName, unsigned resourceType)
    : path(resourcePath), name(resourceName), type(resourceType)
  {
    assert(resourcePath != "" && "Resource path must be not empty.");
    assert(resourceName != "" && "Resource name must be not empty.");
  }

  CoreResourceLoadMessage::~CoreResourceLoadMessage(void)
  {
  }

  unsigned CoreResourceLoadMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceLoad;
  }

  CoreResourceGetMessage::CoreResourceGetMessage(std::string const & resourceName)
    : name(resourceName), resource(0)
  {
    assert(resourceName != "" && "Resource name must be not empty.");
  }

  CoreResourceGetMessage::~CoreResourceGetMessage(void)
  {
  }

  unsigned CoreResourceGetMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceGet;
  }

  CoreResourceStoreMessage::CoreResourceStoreMessage(IResource * resourcePointer, std::string const & resourceName)
    : resource(resourcePointer), name(resourceName)
  {
    assert(resourcePointer != 0 && "Resource pointer must be not NULL.");
    assert(resourceName != "" && "Resource name must be not empty.");
  }
  
  CoreResourceStoreMessage::~CoreResourceStoreMessage(void)
  {
  }

  unsigned CoreResourceStoreMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceStore;
  }

  CoreResourceWriteMessage::CoreResourceWriteMessage(IResource * resourcePointer, std::string const & resourcePath, unsigned resourceType)
    : resource(resourcePointer), path(resourcePath), type(resourceType)
  {
    assert(resourcePointer != 0 && "Resource pointer must be not NULL.");
    assert(resourcePath != "" && "Resource path must be not empty.");
  }

  CoreResourceWriteMessage::~CoreResourceWriteMessage(void)
  {
  }

  unsigned CoreResourceWriteMessage::GetMessageID(void)
  {
    return nsMessageTypes::CoreResourceWrite;
  }

} // namespace nsCore