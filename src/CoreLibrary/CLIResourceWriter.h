#pragma once
#include <string>

namespace nsCore
{

  class IResource;

  class IResourceWriter
  {
  protected:
    virtual ~IResourceWriter(void) {}
  public:
    virtual void Suicide(void) {delete this;}
    virtual void WriteResource(std::string const & path, IResource const * resource) = 0;
  };

} // namespace nsCore