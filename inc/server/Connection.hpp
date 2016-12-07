/*
** Connection.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 14:47:41 2016 Gabriel CADET
** Last update Wed Dec 07 20:30:07 2016 Gabriel CADET
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "ISystem.hpp"
#include "ASocket.hpp"
#include "Socket.hpp"

namespace ecs::system {
  /**
  ** \brief Connection system. Welcome new client and redirect these into the rooms.
  **
  ** The Connection System create a UdpSocket when instanciated.
  **
  ** He will then wait for incoming requests.
  ** When it receive a Request Cost (RC) of 001 (client connection),
  ** it will create an entity, storing client's UID, username, IP and Port, then
  ** notify the client with the response code 002.\n
  ** It'll also answer to 101 RC (rooms status request), by 102 response, containing
  ** rooms informations (name and number of player.).\n
  ** If requested with a 103 RC (room connection request) followed by the room number
  ** or name, he will forward the client to the requested room (through the database).\n
  ** It's now up to the Room system to accept or deny the connection.\n
  **
  */
  class Connection : public ISystem {
    public:
      /**
      ** \brief Default constructor.
      **
      ** Internaly, it create a new UdpSocket.
      */
      Connection();

      /**
      ** \brief Copy constructor. Deleted, because Connection System must not be copyied.
      */
      Connection(Connection const &) = delete;
      /**
      ** \brief Destructor.
      **
      ** Delete internal socket.
      */
      ~Connection() { delete _sock; }

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
    private:
      network::ASocket	*_sock;
  };
} // namespace system

#endif /* !CONNECTION_HPP_ */
