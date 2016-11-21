#pragma once
#include <vector>

namespace nsCore
{

  class ISerializerIn;

  // the purpose of this interface is to provide an easy way to describe a prototype
  // the interface will be consumed by the engine to create a more strict data structure that
  //   can be easily/efficiently read when creating objects
  class IObjectPrototypePattern
  {
  protected:
    virtual ~IObjectPrototypePattern(void) {}
  public:
    virtual void Suicide(void) {delete this;}

    // returns the number of objects required to make this prototype, including the base object
    // for an object with 2 subObjects, it should return 3
    // for an object with 1 subObject that also has a subObject, it should return 3
    virtual unsigned GetTotalNumberOfObjects(void) = 0;

    // returns an unsigned identifier for the base object of this prototype
    virtual unsigned GetBaseObjectId(void) = 0;

    // appends the unsigned identifiers of each child of a given object to a list of identifiers
    virtual void PushBackChildrenIds(unsigned parentId, std::vector<unsigned>& childrenIds) = 0;

    // gets the number of components of a given object inside the prototype
    virtual unsigned GetNumberOfComponentsOfObject(unsigned objectId) = 0;

    // gets the information about a given component of a given object inside the prototype
    virtual void ReadComponentOfObject(unsigned objectId, unsigned componentIndex, unsigned& componentType, ISerializerIn*& componentData) = 0;

    // gets the number of other prototypes used in the construction of this prototype
    virtual unsigned GetNumberOfPrototypesOfObject(unsigned objectId) = 0;
    
    // gets the information about a given prototype of a given object inside the prototype
    virtual void ReadPrototypeOfObject(unsigned objectId, unsigned prototypeIndex, unsigned& prototypeId) = 0;
  };

} // namespace nsCore