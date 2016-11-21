#pragma once
#include <string>

namespace nsCore
{

  class IResource;

  class IResourceReader
  {
  protected:
    virtual ~IResourceReader(void) {}
  public:
    virtual void Suicide(void) {delete this;}
    virtual IResource* ReadResource(std::string const & path) = 0;
  };

} // namespace nsCore