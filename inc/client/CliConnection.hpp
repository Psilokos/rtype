/*
** Connection.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 14:47:41 2016 Gabriel CADET
** Last update Tue Dec 27 17:29:00 2016 Gabriel CADET
*/

#ifndef CLICONNECTION_HPP_
#define CLICONNECTION_HPP_

#include <map>
#include <queue>
#include <tuple>
#include <string>
#include <utility>

#include "ISystem.hpp"
#include "BaseNet.hpp"
#include "ASocket.hpp"
#include "Socket.hpp"

namespace entity_component_system {
  namespace system {
    /**
     ** \brief Connection system. Welcome new client and redirect these into the rooms.
     **
     ** The Connection System create a UdpSocket when instanciated.
     **
     ** He will then wait for an Entity with the Component username..
     ** When ready, it will send a 001 request (client connection) to a server,
     ** it will create an entity, storing client's UID, username, IP and Port, then
     ** wait for either a 002 or the timeout expire.\n
     ** It'll also answer to 101 RC (rooms status request), by 102 response, containing
     ** rooms informations (name and number of player.).\n
     ** If requested with a 103 RC (room connection request) followed by the room number
     ** or name, he will forward the client to the requested room (through the database).\n
     ** It's now up to the Room system to accept or deny the connection.\n
     **
     */
    class Connection : public BaseNet {
      public:
        /**
         ** \brief Default constructor.
         **
         ** Internaly, it create a new UdpSocket.
         */
        Connection(network::UdpSocket *sock);

        /**
         ** \brief Copy constructor. Deleted, because Connection System must not be copyied.
         */
        Connection(Connection const &) = delete;
        /**
         ** \brief Destructor.
         **
         ** Delete internal socket.
         */
        ~Connection() {}

        /**
         ** \brief Assignation operator. Deleted (see copy constructor).
         */
        Connection	&operator=(Connection const &) = delete;

        /**
         ** \brief update function. make the Connection system to run.
         **
         ** See class description.
         **
         ** \param [in, out] db reference on the ECS DataBase. Information are read and stored here.
         ** Permit inter system communications.
         */
        void	update(ecs::database::IDataBase &);

        /*
         ** Private member methods
         */
      private:
        int	rcvRequest(ecs::database::IDataBase &);
        int	req002Handler(ecs::database::IDataBase &db, request *, std::string const &ip, std::string const &port);
        int	req005Handler(ecs::database::IDataBase &db, request *, std::string const &ip, std::string const &port);
        int	req102Handler(ecs::database::IDataBase &db, request *, std::string const &ip, std::string const &port);
        int	req104Handler(ecs::database::IDataBase &db, request *, std::string const &ip, std::string const &port);
        int	req105Handler(ecs::database::IDataBase &db, request *, std::string const &ip, std::string const &port);

        bool	getCliId(ecs::database::IDataBase &db);
        void	addConnectionRequest(ecs::database::IDataBase &db);
        void	addRoomInfoRequest(ecs::database::IDataBase &db);

        void	getServInfo(ecs::database::IDataBase &db, std::string &ip, std::string &port);

        void	getPendingAction(ecs::database::IDataBase &db);

      private:
        typedef std::tuple<std::string, std::string, int, char *> response_t;

        network::ASocket									*_sock;
        std::queue<response_t>			_respQueue;
        std::map<char, int (Connection::*)(ecs::database::IDataBase &, request *, std::string const &, std::string const &)>	_reqHandler;

        typedef decltype(_reqHandler.begin()) reqIter;

        int	_cliId;
        int	_eid;
        int	_roomId;

        bool	_getRoomInfo;

        std::list<pendingAction>	_pending;
    };
  } // namespace system
}

#endif /* !CONNECTION_HPP_ */
