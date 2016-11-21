#include "ICLComponentCollectionCreator.h"
#include "ICLComponentCollection.h"
#include "ICLComponentFactory.h"
#include <cassert>

namespace nsCore
{

  ComponentCollectionCreator::ComponentCollectionCreator(ComponentFactory const * factory)
    : mFactory(factory)
  {
    assert(mFactory != 0 && "Factory pointer must be not NULL.");
  }

  ComponentCollectionCreator::~ComponentCollectionCreator(void)
  {
  }

  void ComponentCollectionCreator::Suicide(void)
  {
  }

  IComponent* ComponentCollectionCreator::CreateComponent(void)
  {
    return new ComponentCollection;
  }

  void ComponentCollectionCreator::DestroyComponent(IComponent* component)
  {
    assert(dynamic_cast<ComponentCollection*>(component) != 0 && "Component passed for destruction doesn't match creator type.");
    ComponentCollection* collection = static_cast<ComponentCollection*>(component);
    std::vector<IComponent*>& subComponents = collection->GetSubComponents();
    for(auto it = subComponents.begin(); it != subComponents.end(); ++it)
    {
      mFactory->DestroyComponent(*it);
    }
    delete collection;
  }

} // namespace nsCore