//
// Transmit.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 31 14:22:17 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 31 19:34:51 2016 Victorien LE COUVIOUR--TUFFET
//

#include "Transmit.hpp"

template<typename>
struct	InitComponentUtils; // i'm coding this shit

template<ecs::database::ComponentTypeID... componentTypesIDs, typename... Components>
struct	InitComponentUtils<ecs::database::ComponentTypes<ecs::database::ComponentTypePair<componentTypesIDs, Components>...>>
{
  template<unsigned idx, typename... ComponentRequestBuilders>
  static std::map<database::ComponentTypeID, std::function<std::unique_ptr<ecs::system::BaseNet::request>(ecs::ID<ecs::Entity> const &, Any const &)>>
  initRequestBuilders(ComponentRequestBuilders&&... componentRequestBuilders, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
  {
    typedef typename RTypeComponents::template GetComponentTypePair<idx>::Type	CTPair;

    static constexpr unsigned	typeID = CTPair::typeID;

    return InitComponentUtils<ecs::database::ComponentTypes<ecs::database::ComponentTypePair<componentTypesIDs, Components>...>>::template
      initRequestBuilders<idx + 1, ComponentRequestBuilders..., std::function<std::unique_ptr<ecs::system::BaseNet::request>(ecs::ID<ecs::Entity> const &, Any const &)>>
      (std::forward<ComponentRequestBuilders>(componentRequestBuilders)...,
       [](ecs::ID<ecs::Entity> const & entityID, Any const & any)
       {
	 // std::cout << any.getValueByRef<typename CTPair::Type>() << std::endl;
       });
  }

  template<unsigned idx, typename... ComponentRequestBuilders>
  static std::map<database::ComponentTypeID, std::function<std::unique_ptr<ecs::system::BaseNet::request>(ecs::ID<ecs::Entity> const &, Any const & any)>>
  initRequestBuilders(ComponentRequestBuilders&&... componentRequestBuilders, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
  {
    return { std::forward<ComponentRequestBuilders>(componentRequestBuilders)... };
  }
};

namespace	entity_component_system::system
{
  void
  Transmit::update(database::IDataBase & db)
  {
    std::list<entity::RTEntity>		rooms = db.getAllEntitiesWithComponent(::roomInfo);
    std::list<entity::RTEntity>		clients = db.getAllEntitiesWithComponent(::userInfo);

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
		if (clientIt->getComponent<component::RoomID>(::roomID).getAttr<::value>() == room.getID())
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
	  std::list<ID<ecs::Entity>>		newClients;
	  std::unique_ptr<network::UDPSocket>	socket;

	  for (auto it = clients.begin(); it != clients.end(); )
	    if (it->getComponent<component::RoomID>(::roomID).getAttr<::value>() == room.getID())
	      {
		newClients.push_back(it->getID());
		it = clients.erase(it);
	      }
	    else
	      ++it;
	  socket->bind("0.0.0.0", std::to_string(5000 + room.getID()));
	  _roomClientsMap.emplace(room.getID(), { std::move(socket) , newClients });
	  db.setComponent(room.getID(), component::ConInfo(db.createAndBindComponent(room.getID(), component::ConInfo, ::conInfo), "0.0.0.0", std::to_string(5000 + room.getID())));
	}
    _initChanges(db);
    _sendChanges(db);
    // 1. init _clientComponentsMap
    // 2. send _clientComponentsMap
    // 3. do select
    // 4. call rcvRequest
  }

  /*
  ** private methods
  */

  void
  Transmit::_initChanges(database::IDataBase & db)
  {
    static std::map<database::ComponentTypeID, std::function<std::unique_ptr<request>
							     (ID<ecs::Entity> const &, Any const &)>> const	componentRequestBuilders = InitComponentUtils<RTypeComponents>::initRequestBuilders<0>();
    std::list<std::tuple<ID<ecs::Entity>, database::ComponentTypeID, Any>>					lastChanges = db.getLastChangesWithComponent(::ttl);

    for (auto & change : lastChanges)
      componentRequestBuilders[std::get<1>(change)](std::get<0>(change), std::get<2>(change));
  }

  void
  Transmit::_sendChanges(database::IDataBase & db)
  {
  }

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
