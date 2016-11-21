#pragma once
#include <hash_map>

namespace nsCore
{

  class ComponentFactory;
  class IMessageManager;
  class IObjectPrototypePattern;
  class ObjectPrototype;

  class PrototypeFactory
  {
  private:
    PrototypeFactory& operator=(PrototypeFactory const &);
  public:
    PrototypeFactory(ComponentFactory* componentFactory);
    ~PrototypeFactory(void);

    void RegisterPrototypePattern(unsigned prototypeId, IObjectPrototypePattern* prototypePattern);
    void CreatePrototype(unsigned prototypeId, IMessageManager* object) const;

  private:
    ComponentFactory* const components;
    std::hash_map<unsigned, ObjectPrototype*> prototypes;
  };

} // namespace nsCore