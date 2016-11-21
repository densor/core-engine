#pragma once
#include "CLSpaces.h"
#include <vector>
#include <hash_set>

namespace nsCore
{

  class IMessage;
  class IMessageHandler;

  class SpaceManager
  {
  public:
    SpaceManager(unsigned numSpaces, unsigned numPositions);
    ~SpaceManager(void);
    
    void Register(unsigned spaceId, unsigned spacePosition, IMessageHandler* handler);
    void Unregister(unsigned spaceId, unsigned spacePosition, IMessageHandler* handler);
    void Activate(unsigned spaceId);
    void Pause(unsigned spaceId);
    void Unpause(unsigned spaceId);
    void TogglePause(unsigned spaceId);
    void Deactivate(unsigned spaceId);
    void GetStateOfSpace(unsigned spaceId, nsSpaces::SpaceStates& current, nsSpaces::SpaceStates& nextFrame);
    void UpdateSpaces(IMessage* activeUpdateMessage, IMessage* pausedUpdateMessage);

  private:
    void UpdateActiveSpaces(void);
    void UpdateListeners(void);
    unsigned GetIndex(unsigned space, unsigned position);

    struct SpaceData
    {
    public:
      SpaceData(void);

      nsSpaces::SpaceStates currentState;
      nsSpaces::SpaceStates nextState;
    };

    struct ListenerUpdate
    {
    public:
      ListenerUpdate(IMessageHandler* listener, unsigned spaceId, unsigned position, unsigned type);
      IMessageHandler* mListener;
      unsigned mSpaceId;
      unsigned mPosition;
      unsigned mType;
    };

    unsigned mNumSpaces;
    unsigned mNumPositions;
    std::hash_set<IMessageHandler*>* mSpaceListeners;
    SpaceData* mSpaces;

    std::vector<ListenerUpdate> mListenerUpdates;
  };

} // namespace nsCore