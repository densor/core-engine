#pragma once
namespace nsCore
{

  namespace nsSpaces
  {

    enum SpaceStates
    {
      InactiveSpace = 0,
      PausedSpace,
      ActiveSpace,
      UnknownSpace // used for initialization of SpaceGetState message result value
    };

    enum SpaceTypes
    {
      RealTimeSpace = 0
    };

  } // namespace nsSpaces

} // namespace nsCore