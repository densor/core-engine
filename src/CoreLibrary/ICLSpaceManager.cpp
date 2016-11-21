#include "ICLSpaceManager.h"
#include "CLIMessageHandler.h"
#include <cassert>
#include <algorithm>

namespace
{

  const unsigned LISTENER_UPDATE_REGISTER = 1;
  const unsigned LISTENER_UPDATE_UNREGISTER = 2;

} // unnamed namespace

namespace nsCore
{

  SpaceManager::SpaceManager(unsigned numSpaces, unsigned numPositions)
    : mNumSpaces(numSpaces), mNumPositions(numPositions)
  {
    assert(numSpaces > 0 && "Number of spaces must be positive.");
    assert(numPositions > 0 && "Number of positions must be positive.");
    mSpaceListeners = new std::hash_set<IMessageHandler*>[numSpaces * numPositions];
    mSpaces = new SpaceData[numSpaces];
  }

  SpaceManager::~SpaceManager(void)
  {
    for(unsigned i = 0; i < mNumSpaces * mNumPositions; ++i)
    {
      assert(mSpaceListeners[i].size() == 0 && "Space listeners aren't being unregistered before destruction of engine.");
    }
    delete [] mSpaces;
    delete [] mSpaceListeners;
  }

  void SpaceManager::Register(unsigned spaceId, unsigned spacePosition, IMessageHandler* handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
    assert(spaceId < mNumSpaces && "Tried to register for a space that doesn't exist.");
    assert(spacePosition < mNumPositions && "Tried to register in a position that doesn't exist.");
    mListenerUpdates.push_back(ListenerUpdate(handler, spaceId, spacePosition, LISTENER_UPDATE_REGISTER));
  }

  void SpaceManager::Unregister(unsigned spaceId, unsigned spacePosition, IMessageHandler* handler)
  {
    assert(handler != 0 && "Handler pointer must be not NULL.");
    assert(spaceId < mNumSpaces && "Tried to unregister from a space that doesn't exist.");
    assert(spacePosition < mNumPositions && "Tried to unregister from a position that doesn't exist.");
    mListenerUpdates.push_back(ListenerUpdate(handler, spaceId, spacePosition, LISTENER_UPDATE_UNREGISTER));
  }

  void SpaceManager::Activate(unsigned spaceId)
  {
    assert(spaceId < mNumSpaces && "Tried to activate a space that doesn't exist.");
    assert(mSpaces[spaceId].currentState != nsSpaces::ActiveSpace && "Tried to activate a space that is already active.");
    assert(mSpaces[spaceId].nextState != nsSpaces::ActiveSpace && "Tried to activate a space that is already being activated.");
    mSpaces[spaceId].nextState = nsSpaces::ActiveSpace;
  }

  void SpaceManager::Pause(unsigned spaceId)
  {
    assert(spaceId < mNumSpaces && "Tried to pause a space that doesn't exist.");
    assert((mSpaces[spaceId].currentState != nsSpaces::InactiveSpace || mSpaces[spaceId].nextState != nsSpaces::InactiveSpace) && "Tried to pause a space that is neither active nor being activated.");
    if(mSpaces[spaceId].nextState != nsSpaces::InactiveSpace)
    {
      mSpaces[spaceId].nextState = nsSpaces::PausedSpace;
    }
  }

  void SpaceManager::Unpause(unsigned spaceId)
  {
    assert(spaceId < mNumSpaces && "Tried to unpause a space that doesn't exist.");
    assert((mSpaces[spaceId].currentState != nsSpaces::InactiveSpace || mSpaces[spaceId].nextState != nsSpaces::InactiveSpace)  && "Tried to unpause a space that is neither active nor being activated.");
    if(mSpaces[spaceId].nextState != nsSpaces::InactiveSpace)
    {
      mSpaces[spaceId].nextState = nsSpaces::ActiveSpace;
    }
  }

  void SpaceManager::TogglePause(unsigned spaceId)
  {
    assert(spaceId < mNumSpaces && "Tried to toggle pause on a space that doesn't exist.");
    assert((mSpaces[spaceId].currentState != nsSpaces::InactiveSpace || mSpaces[spaceId].nextState != nsSpaces::InactiveSpace) && "Tried to toggle pause on a space that is neither active nor being activated.");
    switch(mSpaces[spaceId].nextState)
    {
    case nsSpaces::InactiveSpace:
      break;
    case nsSpaces::PausedSpace:
      mSpaces[spaceId].nextState = nsSpaces::ActiveSpace;
      break;
    case nsSpaces::ActiveSpace:
      mSpaces[spaceId].nextState = nsSpaces::PausedSpace;
      break;
    }
  }

  void SpaceManager::Deactivate(unsigned spaceId)
  {
    assert(spaceId < mNumSpaces && "Tried to deactivate a space that doesn't exist.");
    assert(mSpaces[spaceId].currentState != nsSpaces::InactiveSpace && "Tried to deactivate a space that is not active.");
    assert(mSpaces[spaceId].nextState != nsSpaces::InactiveSpace && "Tried to deactivate a space that is already being deactivated.");
    mSpaces[spaceId].nextState = nsSpaces::InactiveSpace;
  }

  void SpaceManager::GetStateOfSpace(unsigned spaceId, nsSpaces::SpaceStates& current, nsSpaces::SpaceStates& nextFrame)
  {
    assert(spaceId != mNumSpaces && "Tried to get state of a space that doesn't exist.");
    current = mSpaces[spaceId].currentState;
    nextFrame = mSpaces[spaceId].nextState;
  }

  void SpaceManager::UpdateSpaces(IMessage* activeUpdateMessage, IMessage* pausedUpdateMessage)
  {
    assert(activeUpdateMessage != 0 && "Active update message pointer must be not NULL.");
    assert(pausedUpdateMessage != 0 && "Paused update message pointer must be not NULL.");
    for(unsigned j = 0; j < mNumPositions; ++j)
    {
      for(unsigned i = 0; i < mNumSpaces; ++i)
      {
        unsigned index = GetIndex(i, j);
        if(mSpaces[i].currentState != nsSpaces::InactiveSpace)
        {
          IMessage* message = activeUpdateMessage;
          if(mSpaces[i].currentState == nsSpaces::PausedSpace)
          {
            message = pausedUpdateMessage;
          }

          for(auto it = mSpaceListeners[index].begin(); it != mSpaceListeners[index].end(); ++it)
          {
            assert(*it != 0 && "Handler in a space TRAMPLED to invalid value.");
            (*it)->HandleMessage(message);
          }
        }
      }
    }

    UpdateActiveSpaces();
    UpdateListeners();
  }

  void SpaceManager::UpdateActiveSpaces(void)
  {
    for(unsigned i = 0; i < mNumSpaces; ++i)
    {
      mSpaces[i].currentState = mSpaces[i].nextState;
    }
  }

  void SpaceManager::UpdateListeners(void)
  {
    for(unsigned i = 0; i < mListenerUpdates.size(); ++i)
    {
      unsigned index = GetIndex(mListenerUpdates[i].mSpaceId, mListenerUpdates[i].mPosition);
      switch(mListenerUpdates[i].mType)
      {
      case LISTENER_UPDATE_REGISTER:
        assert(mSpaceListeners[index].find(mListenerUpdates[i].mListener) == mSpaceListeners[index].end() && "Attempted to register the same listener to a space position twice.");
        mSpaceListeners[index].insert(mListenerUpdates[i].mListener);
        break;
      case LISTENER_UPDATE_UNREGISTER:
        assert(mSpaceListeners[index].find(mListenerUpdates[i].mListener) != mSpaceListeners[index].end() && "Attempted to unregister an unknown listener from a space position.");
        mSpaceListeners[index].erase(mListenerUpdates[i].mListener);
        break;
      }
    }
    mListenerUpdates.clear();
  }

  unsigned SpaceManager::GetIndex(unsigned space, unsigned position)
  {
    return space * mNumPositions + position;
  }

  SpaceManager::SpaceData::SpaceData(void)
    : currentState(nsSpaces::InactiveSpace), nextState(nsSpaces::InactiveSpace)
  {
  }

  SpaceManager::ListenerUpdate::ListenerUpdate(IMessageHandler* listener, unsigned spaceId, unsigned position, unsigned type)
    : mListener(listener), mSpaceId(spaceId), mPosition(position), mType(type)
  {
  }

} // namespace nsCore