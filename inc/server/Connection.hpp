/*
** Connection.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 14:47:41 2016 Gabriel CADET
** Last update Wed Dec 07 19:36:27 2016 Gabriel CADET
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

//#include "ISystem.hpp"
#include "ASocket.hpp"
#include "Socket.hpp"

namespace ecs::system {
  class Connection : public ISystem {
    public:
      Connection();
      Connection(Connection const &) = delete;
      ~Connection() { delete _sock; }

      Connection	&operator=(Connection const &) = delete;

      void	update(ecs::database::IDataBase &);
    private:
      network::ASocket	*_sock;
  };
} // namespace system

#endif /* !CONNECTION_HPP_ */
