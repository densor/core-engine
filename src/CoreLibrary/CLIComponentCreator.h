#pragma once

namespace nsCore
{

  class IComponent;

  class IComponentCreator
  {
  protected:
    virtual ~IComponentCreator(void) {}
  public:
    virtual void Suicide(void) {delete this;}
    
    virtual IComponent* CreateComponent(void) = 0;
    virtual void DestroyComponent(IComponent* component) = 0;
  };

} // namespace nsCore