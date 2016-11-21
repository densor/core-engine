#pragma once

namespace nsCore
{

  class ISystem;

  class IEngine
  {
  public:
    virtual ~IEngine(void) {}
    virtual void AddSystem(ISystem * system) = 0;
    virtual void Initialize(void) = 0;
    virtual void Run(void) = 0;
  };

} // namespace nsCore