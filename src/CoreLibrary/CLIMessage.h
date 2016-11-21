#pragma once

namespace nsCore
{

  class IMessage
  {
  protected:
    virtual ~IMessage(void) {}

  public:
    virtual unsigned GetMessageID(void) = 0;
  };

} // namespace nsCore