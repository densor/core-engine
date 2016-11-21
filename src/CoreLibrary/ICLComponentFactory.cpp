#include "ICLComponentFactory.h"
#include "CLIComponentCreator.h"
#include "CLIComponent.h"
#include <cassert>

namespace nsCore
{

  ComponentFactory::ComponentFactory(void)
  {
  }

  ComponentFactory::~ComponentFactory(void)
  {
    for(auto it = creators.begin(); it != creators.end(); ++it)
    {
      assert(it->second != 0 && "Creator pointer TRAMPLED to invalid value.");
      it->second->Suicide();
    }
  }

  void ComponentFactory::RegisterComponentCreator(unsigned componentType, IComponentCreator* creator)
  {
    assert(creator != 0 && "Creator pointer must be not NULL.");
    assert(creators.find(componentType) == creators.end() && "Tried to register creator for an already known component type.");
    creators[componentType] = creator;
  }

  IComponent* ComponentFactory::CreateComponent(unsigned componentType) const
  {
    auto it = creators.find(componentType);
    assert(it != creators.end() && "Tried to create a component that doesn't have a registered creator.");
    assert(it->second != 0 && "Creator pointer TRAMPLED to invalid value.");
    return it->second->CreateComponent();
  }

  void ComponentFactory::DestroyComponent(IComponent* component) const
  {
    assert(component != 0 && "Component pointer must be not NULL.");
    auto it = creators.find(component->GetComponentType());
    assert(it != creators.end() && "Tried to destroy a component that doesn't have a registered creator.");
    assert(it->second != 0 && "Creator pointer TRAMPLED to invalid value.");
    it->second->DestroyComponent(component);
  }

} // namespace nsCore