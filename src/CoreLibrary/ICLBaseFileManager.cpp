#include "ICLBaseFileManager.h"
#include "CLIResourceReader.h"
#include "CLIResourceWriter.h"
#include <cassert>

namespace nsCore
{

  BaseFileManager::BaseFileManager(void)
  {
  }

  BaseFileManager::~BaseFileManager(void)
  {
    for(auto it = readerMap.begin(); it != readerMap.end(); ++it)
    {
      it->second->Suicide();
    }
    for(auto it = writerMap.begin(); it != writerMap.end(); ++it)
    {
      it->second->Suicide();
    }
  }

  void BaseFileManager::Store(unsigned type, IResourceReader* reader)
  {
    assert(reader != 0 && "Reader must be not NULL.");
    assert(readerMap.find(type) == readerMap.end() && "Reader already in map.");
    readerMap[type] = reader;
  }

  void BaseFileManager::Store(unsigned type, IResourceWriter* writer)
  {
    assert(writer != 0 && "Writer must be not NULL.");
    assert(writerMap.find(type) == writerMap.end() && "Writer already in map.");
    writerMap[type] = writer;
  }

  IResource* BaseFileManager::ReadResource(unsigned type, std::string const & path)
  {
    auto it = readerMap.find(type);
    assert(path != "" && "Resource path must be not empty.");
    assert(it != readerMap.end() && "Unknown reader requested.");
    assert(it->second != 0 && "Reader TRAMPLED to invalid value.");
    return it->second->ReadResource(path);
  }

  void BaseFileManager::WriteResource(unsigned type, std::string const & path, IResource const * resource)
  {
    auto it = writerMap.find(type);
    assert(path != "" && "Resource path must be not empty.");
    assert(resource != 0 && "Resource pointer must be not NULL.");
    assert(it != writerMap.end() && "Unknown writer requested.");
    assert(it->second != 0 && "Writer TRAMPLED to invalid value.");
    it->second->WriteResource(path, resource);
  }

} // namespace nsCore