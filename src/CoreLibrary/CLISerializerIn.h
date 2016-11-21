#pragma once
#include <BaseTsd.h>
#include <string>

namespace nsCore
{

  class ISerializerIn
  {
  protected:
    virtual ~ISerializerIn(void) {}
  public:
    virtual void Acquire(void) = 0;
    virtual void Release(void) = 0;
    virtual unsigned ReadFloats(float* to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadDoubles(double* to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadChars(PINT8 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadUnsignedChars(PUINT8 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadShorts(PINT16 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadUnsignedShorts(PUINT16 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadInt32s(PINT32 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadUnsignedInt32s(PUINT32 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadInt64s(PINT64 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadUnsignedInt64s(PUINT64 to, unsigned number, unsigned start) = 0;
    virtual unsigned ReadString(std::string* to, unsigned start) = 0;
    virtual unsigned ReadNumbers(unsigned* to, unsigned number, unsigned start) = 0;
  };

} // namespace nsCore