#include "ICLPrototypeFactory.h"
#include "CLIMessageManager.h"
#include "ICLObjectPrototype.h"
#include <cassert>

namespace nsCore
{

  PrototypeFactory::PrototypeFactory(ComponentFactory* componentFactory)
    : components(componentFactory)
  {
    assert(componentFactory != 0 && "Component factory pointer must be not NULL.");
  }

  PrototypeFactory::~PrototypeFactory(void)
  {
    assert(components != 0 && "Component factory pointer TRAMPLED to invalid value.");
    for(auto it = prototypes.begin(); it != prototypes.end(); ++it)
    {
      assert(it->second != 0 && "Prototype pointer TRAMPLED to invalid value.");
      delete it->second;
    }
  }

  void PrototypeFactory::RegisterPrototypePattern(unsigned prototypeId, IObjectPrototypePattern* prototypePattern)
  {
    assert(components != 0 && "Component factory pointer TRAMPLED to invalid value.");
    assert(prototypes.find(prototypeId) == prototypes.end() && "Tried to register duplicate prototype.");
    assert(prototypePattern != 0 && "Prototype pattern pointer must be not NULL.");
    prototypes[prototypeId] = new ObjectPrototype(prototypePattern);
  }

  void PrototypeFactory::CreatePrototype(unsigned prototypeId, IMessageManager* object) const 
  {
    auto it = prototypes.find(prototypeId);
    assert(components != 0 && "Component factory pointer TRAMPLED to invalid value.");
    assert(it != prototypes.end() && "Tried to create unknown prototype.");
    assert(object != 0 && "Object pointer must be not NULL.");
    assert(it->second != 0 && "Prototype TRAMPLED to invalid value.");
    it->second->BuildObject(object, components, this);
  }

}