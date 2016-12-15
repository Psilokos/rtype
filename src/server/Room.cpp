/*
** Room.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 14 16:34:13 2016 Gabriel CADET
** Last update Thu Dec 15 19:23:47 2016 Gabriel CADET
*/

#include "Room.hpp"

namespace ecs::system {
  Room::Room(unsigned int minRoom, unsigned char slots, bool spect, int maxRoom)
  : _minRoom(minRoom), _slots(slots), _spect(spect), _maxRoom(maxRoom)
  {}

  void						Room::update(ecs::database::IDataBase &db) {
    std::vector<ecs::database::Entity *>	ents;

    manageRoomEntities(db, ents);
  }

  ecs::database::Entity		*Room::addRoomEntity(ecs::database::IDataBase &db) const {
    int				eid;
    ecs::database::Component	*RoomInfo = new ecs::database::Component({ "Id", "Slots", "Clients", "Spect", "GameState" });

    eid = db.addEntity();
    db.bindComponent("RoomInfo", RoomInfo, eid);
    RoomInfo->setAttr<int>("Id", eid);
    RoomInfo->setAttr<char>("Slots", _slots);
    RoomInfo->setAttr<char>("Clients", 0);
    RoomInfo->setAttr<bool>("Spect", _spect);
    RoomInfo->setAttr<int>("GameState", 0);
    return db.getEntityById(eid);
  }

  void				Room::manageRoomEntities(ecs::database::IDataBase &db, std::vector<ecs::database::Entity *> &ents) const {
    ents = db.getEntitiesWithComponents("RoomInfo");

    if (ents.size() < _minRoom) {
      for (int i = ents.size(); i < _minRoom; ++i) {
        ents.push_back(addRoomEntity(db));
      }
    }
    else {
      bool	full = true;
      for (auto ent : ents) {
        if (ent->getComponent("RoomInfo")->getAttr<char>("Clients") < _slots) {
          full = false;
          break ;
        }
      }

      if (full && ents.size() < _maxRoom) {
        ents.push_back(addRoomEntity(db));
      }
      else if (ents.size() > _minRoom) {
        int	nb = ents.size() - _minRoom;

        std::remove_if(ents.begin(), ents.end(), [this, &nb](ecs::database::Entity *ent)-> bool {
            if (nb > this->_minRoom && ent->getComponent("Clients")->getAttr<char>("Clients") == 0) {
              --nb;
              return true;
            }
            return false;
        });
      }
    }
  }
} // namespace ecs::system
