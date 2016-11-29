/*
** WinSock.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 14:42:42 2016 Gabriel CADET
** Last update Tue Nov 29 15:02:21 2016 Gabriel CADET
*/

#ifndef WINSOCK_HPP_
#define WINSOCK_HPP_

#include "ASocket.hpp"

namespace network {
  class WinSock : public ASocket {
    public:
      WinSock(int domain, int type, int protocol);
      WinSock(WinSock const &) = delete;
      ~WinSock();

      WinSock &operator=(WinSock const &) = delete;

    public:
      static int	nbSock;
      static WSADATA	wsaData;
  };
} // namespace network
#endif /* !WINSOCK_HPP_ */
