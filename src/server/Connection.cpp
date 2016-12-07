/*
** Connection.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 17:48:36 2016 Gabriel CADET
** Last update Wed Dec 07 19:41:45 2016 Gabriel CADET
*/

#include "Connection.hpp"

namespace ecs::system {
  Connection::Connection()
    : _sock(new network::UdpSocket())
  {}

  void	Connection::update(ecs::database::IDataBase &db) {

  }

} // namespace system
