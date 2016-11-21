#pragma once

namespace nsCore
{

  class IThreadTask;

  class IThreadManager
  {
  protected:
    virtual ~IThreadManager(void) {}

  public:
      // called to wait for all tasks that block the specified id to finish
    virtual void Synchonize(unsigned blockId) = 0;

      // the blockId for the end of the frame
    static const unsigned BLOCKID_END_OF_FRAME;
  };

} // namespace nsCore