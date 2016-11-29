/*
** WinSock.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 14:55:13 2016 Gabriel CADET
** Last update Tue Nov 29 15:04:36 2016 Gabriel CADET
*/

#include "WinSock.hpp"

namespace network {
  int WinSock::nbSock = 0;
  WSADATA WinSock::wsaData;

  WinSock::WinSock(int domain, int type, int protocol)
  :ASocket()
  {
    if (nbSock == 0) {
      int res;
      res = WSAStartup(MAKEWORD(2,2), &wsaData);
      if (res != 0)
        throw;
    }
    _sock = socket(domain, type, protocol);

  }
} // namespace network
