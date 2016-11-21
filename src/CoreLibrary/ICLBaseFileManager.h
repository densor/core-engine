#pragma once
#include <string>
#include <hash_map>

namespace nsCore
{

  class IResourceReader;
  class IResourceWriter;
  class IResource;

  class BaseFileManager
  {
  public:
    BaseFileManager(void);
    ~BaseFileManager(void);

    void Store(unsigned type, IResourceReader* reader);
    void Store(unsigned type, IResourceWriter* writer);

    IResource* ReadResource(unsigned type, std::string const & path);
    void WriteResource(unsigned type, std::string const & path, IResource const * resource);

  private:
    std::hash_map<unsigned, IResourceReader*> readerMap;
    std::hash_map<unsigned, IResourceWriter*> writerMap;
    IResourceReader* defaultLoader;
    IResourceWriter* defaultWriter;
  };

} // namespace nsCore