#pragma once

namespace nsCore
{

  namespace nsMessageTypes
  {

    enum MessageType
    {
      CoreQuit = 0,
      CoreInitialize, // sent when the engine starts for the first time - should be when all intersystem initialization occurs
      CoreFinalize, // sent right before the game loop begins - should be when all post intersystem initialization occurs
      CoreSpaceRegister, // registers an update function for a space
      CoreSpaceUnregister, // unregisters an update function for a space
      CoreSpaceActivate, // activates a space, so update messages are sent to it
      CoreSpacePause, // pauses a space, which affects some update messages
      CoreSpaceUnpause, // unpauses a space, which affects some update messages
      CoreSpaceTogglePause, // toggles the pause state of a space
      CoreSpaceDeactivate, // deactivates a space, so update messages are not sent to it
      CoreSpaceGetState, // gets whether a space is receiving updates
      CoreSpaceUpdate, // sent to all listeners of active or paused spaces with elapsed times - number of elapsed times is not defined here
      CoreResourceStoreReader, // stores a method for reading from a URI
      CoreResourceStoreWriter, // sotres a method for writing to a URI
      CoreResourceLoad, // loads a resource from a URI if it isn't already loaded
      CoreResourceGet, // gets a loaded resource by name
      CoreResourceStore, // stores a resource in the manager's storage if nothing is already stored under the requested name
      CoreResourceWrite, // writes a resource to a URI
      CoreObjectManagerRegisterComponent, // register a component with the object manager
      CoreObjectManagerRegisterPrototype, // register an object prototype with the object manager
      CoreObjectManagerCreateObject, // requests the object manager to create an object from an object prototype
      CoreObjectManagerDestroyObject, // requests the object manager to destroy an object
      CoreObjectRegisterComponent, // registers a component with an object
      CoreObjectSendMessageUpwards, // sends a message to the component's parent objects and sibling objects
      CoreObjectSendMessageDownwards, // sends a message to the component's child objects and sibling objects
      CoreObjectGetRootObject, // gets the root component of an object from any sub-object
      NumMessageTypes
    };

  } // namespace nsMessageTypes

} // namespace nsCore