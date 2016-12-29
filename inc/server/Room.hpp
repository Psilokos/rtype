/*
** Room.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 14 16:33:31 2016 Gabriel CADET
** Last update Thu Dec 29 17:27:41 2016 Gabriel CADET
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <algorithm>

#include "ISystem.hpp"

#include "IDataBase.hpp"

namespace entity_component_system::system {
  /**
  ** \brief Room system.
  **
  ** The Room subsystem is charged to manage all the rooms Entity.
  **
  ** Here are the few rules:
  ** - There MUST be at least [minRoom], able of accepting up to [slots] players.
  ** - If all Rooms are full, a new one is created.
  ** - If a Room is empty, it is deleted IF nbRooms > minRooms.
  ** - The roomSystem will NOT manage it's player. (The Connection System will update the player number of each rooms).
  ** - Although it create it, the room MUST NOT update it's GameState.
  */
  class Room : public ISystem {
    public:
      /**
      ** \brief Room Constructor. Allow to customize rooms info.
      **
      ** If not handled by other Systems, use the defaults params.
      **
      ** \param [in] minRoom Minimum number of room to be kept launched.
      ** \param [in] slots Number of slots per rooms.
      ** \param [in] spect Boolean to enable spectating.
      ** \param [in] maxRoom Maximum number of room to be created.
      */
      Room(unsigned int minRoom = 4, unsigned char slots = 4, bool spect = false, int maxRoom = 16);

      /**
      ** \brief Copy constructor. Deleted because systems MUST NOT be copied.
      */
      Room(Room const &oth) = delete;

      /**
      ** \brief Default destructor. Destruct the object (Obviously, duuh)
      */
      ~Room() {}

      /**
      ** \brief Assignation operator. Deleted (see copy constructor).
      */
      Room	&operator=(Room const &oth) = delete;

      /**
      ** \brief update function. The entrypoint of the system.
      **
      ** See class description.
      **
      ** \param [in, out] db Reference on the ecs database.
      */
      void	update(ecs::database::IDataBase &db);

    private:
      void	manageRoomEntities(ecs::database::IDataBase &db, std::list<ecs::entity::RTEntity> &ents) const;
      ecs::entity::RTEntity	&addRoomEntity(ecs::database::IDataBase &db) const;

    private:
      unsigned int	_minRoom;
      unsigned char	_slots;
      bool		_spect;
      int		_maxRoom;
  };
} // namespace ecs::system
#endif /* !ROOM_HPP_ */
