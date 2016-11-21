#pragma once
#include <vector>

namespace nsCore
{

  class IObjectPrototypePattern;
  class IMessageManager;
  class ComponentFactory;
  class ISerializerIn;
  class PrototypeFactory;

  class ObjectPrototype
  {
  private:
    ObjectPrototype& operator=(ObjectPrototype const &);
  public:
    ObjectPrototype(IObjectPrototypePattern* pattern);
    ~ObjectPrototype(void);
    void BuildObject(IMessageManager* parentObject, ComponentFactory const * factory, PrototypeFactory const * otherPrototypes) const;

  private:
    void ReadObject(std::vector<std::pair<unsigned, ISerializerIn*> >& objectData, IObjectPrototypePattern* pattern, unsigned objectId);
    void BuildObject(IMessageManager* parentObject, ComponentFactory const * factory, PrototypeFactory const * otherPrototypes, std::vector<std::pair<unsigned, ISerializerIn*> > const & objectData) const;

    // vector of <parent index, object data>
    //   object data is vector of <component id/prototype id, component data/NULL>
    std::vector<std::pair<unsigned, std::vector<std::pair<unsigned, ISerializerIn*> > > > subObjects;
  };

} // namespace nsCore