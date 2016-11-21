#pragma once
#include <hash_map>

namespace nsCore
{

  class IComponent;
  class IComponentCreator;

  class ComponentFactory
  {
  public:
    ComponentFactory(void);
    ~ComponentFactory(void);

    void RegisterComponentCreator(unsigned componentType, IComponentCreator* creator);
    IComponent* CreateComponent(unsigned componentType) const;
    void DestroyComponent(IComponent* component) const;

  private:
    std::hash_map<unsigned, IComponentCreator*> creators;
  };

} // namespace nsCore