/*
** Room.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 14 16:34:13 2016 Gabriel CADET
** Last update Thu Dec 29 17:44:00 2016 Gabriel CADET
*/

#include "Room.hpp"

namespace entity_component_system::system {
  Room::Room(unsigned int minRoom, unsigned char slots, bool spect, int maxRoom)
  : _minRoom(minRoom), _slots(slots), _spect(spect), _maxRoom(maxRoom)
  {}

  void						Room::update(ecs::database::IDataBase &db) {
    std::list<ecs::entity::RTEntity>	ents;

    manageRoomEntities(db, ents);
  }

  ecs::entity::RTEntity		&Room::addRoomEntity(ecs::database::IDataBase &db) const {
    ecs::entity::Room	room;

    room.getComponent<::RoomInfo>().setAttr<::slots>(_slots);
    room.getComponent<::RoomInfo>().setAttr<::clients>(0);
    room.getComponent<::RoomInfo>().setAttr<::spectate>(_spect);
    room.getComponent<::RoomInfo>().setAttr<::gamestate>(0);

    db.createEntityFromAssembly(room);
    return db.getEntity(room.getID()).getValueByRef<entity::RTEntity>();
  }

  void		Room::manageRoomEntities(ecs::database::IDataBase &db, std::list<ecs::entity::RTEntity> &ents) const {
    ents = db.getAllEntitiesWithComponent(ecs::database::ComponentTypeID::RoomInfo);

    if (ents.size() < _minRoom) {
      for (int i = ents.size(); i < _minRoom; ++i) {
        ents.push_back(addRoomEntity(db));
      }
    }
    else {
      bool	full = true;
      for (auto &ent : ents) {
        if (ent.getComponent<component::RoomInfo>("RoomInfo").getAttr<::clients>() < _slots) {
          full = false;
          break ;
        }
      }

      if (full && ents.size() < _maxRoom) {
        addRoomEntity(db);
      }
      else if (ents.size() > _minRoom) {
        int	nb = ents.size() - _minRoom;

        std::remove_if(ents.begin(), ents.end(), [this, &nb](ecs::entity::RTEntity &ent) -> bool {
            if (nb > this->_minRoom && ent.getComponent<component::RoomInfo>("RoomInfo").getAttr<::clients>() == 0) {
              --nb;
              return true;
            }
            return false;
        });
      }
    }
  }
} // namespace ecs::system
