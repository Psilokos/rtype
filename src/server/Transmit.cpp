//
// Transmit.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 31 14:22:17 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 31 18:07:53 2016 Victorien LE COUVIOUR--TUFFET
//

#include "Transmit.hpp"

// clientAssembly: userInfo { string: pseudo } | conInfo { string: ip, string: port } |

namespace	entity_component_system::system
{
  void
  Transmit::update(database::IDataBase & db)
  {
    std::list<entity::RTEntity>		rooms = db.getAllEntitiesWithComponent(::RoomInfo);
    std::list<entity::RTEntity>		clients = db.getAllEntitiesWithComponent(::UserInfo);

    for (auto it = clients.begin(); it != clients.end(); )
      if (!it->hasComponent(::RoomID))
	it = clients.erase(it);
      else
	++it;
    for (auto it = _roomClientsMap.begin(); it != _roomClientsMap.end(); )
      {
	bool	isFound = false;

	for (auto clientIt = it->second.begin(); clientIt != it->second.end(); )
	  {
	    bool	isClientFound = false;

	    for (auto & client : clients)
	      if (client.getID() == *clientIt)
		isClientFound = true;
	    if (!isClientFound)
	      clientIt = it->second.erase(clientIt);
	    else
	      ++clientIt;
	  }
	for (auto & room : rooms)
	  if (room.getID() == it->first)
	    {
	      isFound = true;
	      for (auto clientIt = clients.begin(); clientIt != clients.end(); )
		if (clientIt->getComponent<component::RoomID>(::RoomID).getAttr<::value>() == room.getID())
		  {
		    if (it->second.find(clientIt->getID()) == it->second.end())
		      {
			it->second.push_back(clientIt->getID());
			clientIt = clients.erase(clientIt);
		      }
		  }
		else
		  ++it;
	      break;
	    }
	if (!isFound)
	  it = _roomClientsMap.erase(it);
	else
	  ++it;
      }
    for (auto & room : rooms)
      if (_roomClientsMap.find(room.getID()) == _roomClientsMap.end())
	{
	  std::list<ID<ecs::Entity>>	newClients;
	  std::unique_ptr<UDPSocket>	socket;

	  for (auto it = clients.begin(); it != clients.end(); )
	    if (it->getComponent<component::RoomID>(::RoomID).getAttr<::value>() == room.getID())
	      {
		newClients.push_back(it->getID());
		it = clients.erase(it);
	      }
	    else
	      ++it;
	  socket->bind("0.0.0.0", std::to_string(5000 + room.getID()));
	  _roomClientsMap.emplace(room.getID(), { std::move(socket) , newClients });
	  db.setComponent(room.getID(), component::ConInfo(db.createAndBindComponent(room.getID(), component::ConInfo, ::ConInfo), "0.0.0.0", std::to_string(5000 + room.getID())));
	}
    // 1. init _clientComponentsMap
    // 2. send _clientComponentsMap
    // 3. do select
    // 4. call rcvRequest
  }

  /*
  ** private methods
  */

  int
  Transmit::_rcvRequest(ecs::database::IDataBase & db)
  {
  }

  int
  Transmit::_req005Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) // not supposed to receive
  {
  }

  int
  Transmit::_req201Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req202Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req203Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req204Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req301Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req302Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }

  int
  Transmit::_req303Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port)
  {
  }
}
