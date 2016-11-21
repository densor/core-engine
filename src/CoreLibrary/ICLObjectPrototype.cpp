#include "ICLObjectPrototype.h"
#include "CLIObjectPrototypePattern.h"
#include "ICLComponentFactory.h"
#include "CLISerializerIn.h"
#include "CLIComponent.h"
#include "CLObjectMessages.h"
#include "CLIMessageManager.h"
#include "CLComponentEnumeration.h"
#include "ICLComponentCollection.h"
#include "ICLPrototypeFactory.h"
#include <cassert>

namespace nsCore
{

  ObjectPrototype::ObjectPrototype(IObjectPrototypePattern* pattern)
  {
    assert(pattern != 0 && "Pattern pointer must be not NULL.");
    unsigned numObjects = pattern->GetTotalNumberOfObjects();
    assert(numObjects > 0 && "Pattern must contain at least one object.");
    std::vector<unsigned> objectIds;
    subObjects.resize(numObjects);
    objectIds.push_back(pattern->GetBaseObjectId());
    ReadObject(subObjects[0].second, pattern, objectIds[0]);
    unsigned firstChild = objectIds.size();
    pattern->PushBackChildrenIds(objectIds[0], objectIds);
    for(firstChild; firstChild < objectIds.size(); ++firstChild)
    {
      subObjects[firstChild].first = 0;
    }
    for(unsigned i = 1; i < numObjects; ++i)
    {
      assert(i < objectIds.size() && "Subobjects of prototype not populated by pattern.");
      ReadObject(subObjects[i].second, pattern, objectIds[i]);
      pattern->PushBackChildrenIds(objectIds[i], objectIds);
      for(firstChild; firstChild < objectIds.size(); ++firstChild)
      {
        subObjects[firstChild].first = i;
      }
    }
    assert(objectIds.size() == numObjects && "Number of objects incorrect.");
    for(unsigned i = 1; i < numObjects; ++i)
    {
      assert(subObjects[i].first < i && "Parentage of children objects incorrect.");
    }
  }

  ObjectPrototype::~ObjectPrototype(void)
  {
    assert(subObjects.size() > 0 && "Prototype data TRAMPLED to invalid value.");
    for(unsigned i = 0; i < subObjects.size(); ++i)
    {
      for(auto it = subObjects[i].second.begin(); it != subObjects[i].second.end(); ++it)
      {
        assert(it->second != 0 && "Component data TRAMPLED to invalid value.");
        it->second->Release();
      }
    }
  }

  void ObjectPrototype::BuildObject(IMessageManager* parentObject, ComponentFactory const * factory, PrototypeFactory const * otherPrototypes) const
  {
    assert(parentObject != 0 && "Parent pointer must be not NULL.");
    assert(factory != 0 && "Factory pointer must be not NULL.");
    assert(otherPrototypes != 0 && "Prototypes pointer must be not NULL.");
    assert(subObjects.size() > 0 && "Prototype data TRAMPLED to invalid value.");
    std::vector<IMessageManager*> objects(subObjects.size(), 0);
    objects[0] = parentObject;
    BuildObject(objects[0], factory, otherPrototypes, subObjects[0].second);
    for(unsigned i = 1; i < subObjects.size(); ++i)
    {
      assert(subObjects[i].first < i && "Object data TRAMPLED to invalid value.");
      IComponent* component = factory->CreateComponent(nsComponentIds::ComponentCollection);
      assert(component != 0 && "Component was not created.");
      assert(dynamic_cast<ComponentCollection*>(component) != 0 && "Component was not of expected type.");
      objects[i] = static_cast<ComponentCollection*>(component);
      CoreObjectRegisterComponentMessage msg(component);
      objects[subObjects[i].first]->HandleMessage(&msg);
      BuildObject(objects[i], factory, otherPrototypes, subObjects[i].second);
    }
  }

  void ObjectPrototype::ReadObject(std::vector<std::pair<unsigned, ISerializerIn*> >& objectData, IObjectPrototypePattern* pattern, unsigned objectId)
  {
    assert(pattern != 0 && "Pattern pointer must be not NULL.");
    assert(objectData.size() == 0 && "Object data already populated.");
    unsigned numComponents = pattern->GetNumberOfComponentsOfObject(objectId);
    unsigned numPrototypes = pattern->GetNumberOfPrototypesOfObject(objectId);
    assert(numComponents + numPrototypes > 0 && "Object has no components or prototypes.");
    objectData.resize(numComponents + numPrototypes);
    for(unsigned i = 0; i < numComponents; ++i)
    {
      pattern->ReadComponentOfObject(objectId, i, objectData[i].first, objectData[i].second);
      assert(objectData[i].second != 0 && "Component data pointer must be not NULL.");
      objectData[i].second->Acquire();
    }
    for(unsigned i = 0; i < numPrototypes; ++i)
    {
      pattern->ReadPrototypeOfObject(objectId, i, objectData[i + numComponents].first);
      objectData[i + numComponents].second = 0;
    }
  }

  void ObjectPrototype::BuildObject(IMessageManager* parentObject, ComponentFactory const * factory, PrototypeFactory const * otherPrototypes, std::vector<std::pair<unsigned, ISerializerIn*> > const & objectData) const
  {
    assert(parentObject != 0 && "Parent pointer must be not NULL.");
    assert(factory != 0 && "Factory pointer must be not NULL.");
    assert(otherPrototypes != 0 && "Prototypes pointer must be not NULL.");
    for(auto it = objectData.begin(); it != objectData.end(); ++it)
    {
      if(it->second == 0) // prototype
      {
        otherPrototypes->CreatePrototype(it->first, parentObject);
      }
      else
      {
        IComponent* component = factory->CreateComponent(it->first);
        assert(component != 0 && "Component was not created.");
        component->SerializeIn(it->second);
        CoreObjectRegisterComponentMessage msg(component);
        parentObject->HandleMessage(&msg);
      }
    }
  }

} // namespace nsCore