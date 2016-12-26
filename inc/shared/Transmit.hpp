/*
** TransmitSrv.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 23 16:04:27 2016 Gabriel CADET
** Last update Mon Dec 26 15:19:22 2016 Gabriel CADET
*/

#ifndef TRANSMIT_HPP_
#define TRANSMIT_HPP_

#include <map>
#include <queue>
#include <list>
#include <tuple>
#include <string>
#include <utility>

#include "ISystem.hpp"
#include "BaseNet.hpp"
#include "ASocket.hpp"
#include "Socket.hpp"

#include "MockDb.hpp"

namespace ecs::system {
  /**
  ** \brief Transmition system.
  **
  ** The Transmition system is charged of transmiting game info to clients, as well as answering to several request.
  ** If it's in the client, it'll send move info to the server.
  **
  ** When Server-side, the Transmition create a new UDPSocket for each room, and send info to connected clients.
  **
  ** When Client-side, it receive an UDPSocket in it's construction.
  **
  ** Information to be sent has a TTL : that is, important informations will be sent several time, so that client will receive these.
  ** These data will be stored in a list, and pop if TTL become 0 or if the client respond with a OK (005) followed by a correct token representing the info.
  **
  ** Only some information will be sent, those are :
  **  - Room info (for the room the client is in).
  **  - Game info
  **  - Death or birth info (high importance)
  **  - position infos (low priority)
  **
  ** It'll send these info for each room, to each clients connected in the room.
  **
  ** The comportement of the Tranmsition system, such as the request it can receive and Handle, is define by the presence or absence of a UDPSocket
  ** during it's construction.
  **/
  class Transmition : public BaseNet {
    public:
      /**
      ** \brief Default constructor. Use when Server-side.
      */
      Transmition();

      /**
      ** \brief Client-side constructor.
      **
      ** \param [in] sock UDPSocket to be used to send and receive data.
      */
      Transmition(network::UDPSocket *sock);

      /**
      ** \brief Copy constructor. Deleted, as System must not be copyied.
      */
      Transmition(Tranmsition const &oth) = delete;

      /**
      ** \brief Destructor.
      **
      ** Delete internal socket, if serverSide.
      */
      ~Transmition();

      /**
      ** \brief Assignation operator. Deleted.
      */
      Transmition	&operator=(Transmition const &oth) = delete;

      /**
      ** \brief Update function. System entry point.
      **
      ** For more info , see class description.
      **
      ** \param [in, out] db Reference on the ECS DataBase.
      */
      void	update(ecs::database::IDataBase &db);

      /*
      ** Private member methods.
      */
    private:
      int	rcvRequest(ecs::database::IDataBase &);

      int	req005Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req201Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req202Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req203Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req204Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req301Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req302Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);
      int	req303Handle(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port);

    private:
      typedef std::tuple<std::string, std::string, int, char *>	message_t;
      typedef std::list<message_t>				msgQueue_t;

      bool			_clientSide;
  };
} // namespace ecs::system

#endif /* !TRANSMITSRV_HPP_ */
