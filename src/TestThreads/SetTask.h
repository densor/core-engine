#include "CLIThreadTask.h"

namespace nsCore
{

  namespace nsTest
  {

    class SetTaskInt : public nsCore::IThreadTask
    {
    public:
      SetTaskInt(int* address, int value, std::vector<unsigned> const & blocked);
      virtual ~SetTaskInt(void);

      virtual void Execute(IThreadTaskScheduler* threadManager);
      virtual void Suicide(void);

      virtual std::vector<unsigned> const & GetBlocked(void);

    private:
      SetTaskInt& operator=(SetTaskInt&);
      SetTaskInt(SetTaskInt&);

      int * const mAddress;
      int const mValue;
      std::vector<unsigned> const & mBlocked;
    };

  } // namespace nsTest

} // namespace nsCore