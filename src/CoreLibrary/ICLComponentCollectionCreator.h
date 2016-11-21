#pragma once
#include "CLIComponentCreator.h"

namespace nsCore
{

  class ComponentFactory;

  class ComponentCollectionCreator : public IComponentCreator
  {
  public:
    ComponentCollectionCreator(ComponentFactory const * factory);
    virtual ~ComponentCollectionCreator(void);
    virtual void Suicide(void);
    virtual IComponent* CreateComponent(void);
    virtual void DestroyComponent(IComponent* component);

  private:
    ComponentCollectionCreator& operator=(ComponentCollectionCreator&);

    ComponentFactory const * const mFactory;
    // TODO: object pool or other memory management solution
  };

} // namespace nsCore