#pragma once
#include "CLIMessage.h"
#include <string>

namespace nsCore
{

  class IResource;
  class IResourceReader;
  class IResourceWriter;
  class ISmartResource;

  class CoreResourceStoreReaderMessage : public IMessage
  {
  private:
    CoreResourceStoreReaderMessage& operator=(CoreResourceStoreReaderMessage const &);
  public:
    CoreResourceStoreReaderMessage(unsigned resourceType, IResourceReader* resourceReader);
    virtual ~CoreResourceStoreReaderMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const type;
    IResourceReader * const reader;
  };

  class CoreResourceStoreWriterMessage : public IMessage
  {
  private:
    CoreResourceStoreWriterMessage& operator=(CoreResourceStoreWriterMessage const &);
  public:
    CoreResourceStoreWriterMessage(unsigned resourceType, IResourceWriter* resourceWriter);
    virtual ~CoreResourceStoreWriterMessage(void);
    virtual unsigned GetMessageID(void);

    unsigned const type;
    IResourceWriter * const writer;
  };

  class CoreResourceLoadMessage : public IMessage
  {
  private:
    CoreResourceLoadMessage& operator=(CoreResourceLoadMessage const &);
  public:
    CoreResourceLoadMessage(std::string const & resourcePath, std::string const & resourceName, unsigned resourceType);
    virtual ~CoreResourceLoadMessage(void);
    virtual unsigned GetMessageID(void);

    std::string const & path;
    std::string const & name;
    unsigned const type;
  };

  class CoreResourceGetMessage : public IMessage
  {
  private:
    CoreResourceGetMessage& operator=(CoreResourceGetMessage const &);
  public:
    CoreResourceGetMessage(std::string const & resourceName);
    virtual ~CoreResourceGetMessage(void);
    virtual unsigned GetMessageID(void);

    std::string const & name;
    ISmartResource* resource;
  };

  class CoreResourceStoreMessage : public IMessage
  {
  private:
    CoreResourceStoreMessage& operator=(CoreResourceStoreMessage const &);
  public:
    CoreResourceStoreMessage(IResource * resourcePointer, std::string const & resourceName);
    virtual ~CoreResourceStoreMessage(void);
    virtual unsigned GetMessageID(void);

    IResource * const resource;
    std::string const & name;
  };

  class CoreResourceWriteMessage : public IMessage
  {
  private:
    CoreResourceWriteMessage& operator=(CoreResourceWriteMessage const &);
  public:
    CoreResourceWriteMessage(IResource * resourcePointer, std::string const & resourcePath, unsigned resourceType);
    virtual ~CoreResourceWriteMessage(void);
    virtual unsigned GetMessageID(void);

    IResource * const resource;
    std::string const & path;
    unsigned const type;
  };

} // namespace nsCore