/*
** ASocket.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 13:59:41 2016 Gabriel CADET
** Last update Tue Nov 29 14:42:07 2016 Gabriel CADET
*/

#include "ASocket.hpp"

namespace network {
  ASocket::ASocket() {
#ifdef __linux__
    _sock = -1;
#else
    _sock = INVALID_SOCKET;
  }
} // namespace network
