/*
** ASocket.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 13:59:41 2016 Gabriel CADET
** Last update Fri Dec 02 19:39:39 2016 Gabriel CADET
*/

#include "ASocket.hpp"

namespace network {
#ifdef _WIN32
  int		ASocket::nbSock = 0;
  WSADATA	ASocket::wsaData;
#endif

  int ASocket::shutdown(How flgs)
  {
    int   ret;
    ret = ::shutdown(_sock, flgs);
#ifdef __linux__
    if (ret == -1)
#else
    if (ret == SOCKET_ERROR)
#endif
      return -1;
    return ret;
  }

  int ASocket::select(std::list<ASocket*>& read, std::list<ASocket*>& write, std::list<ASocket*>& exept, timeval * timeout)
  {
    int ret;
    fd_set rd;
    fd_set wr;
    fd_set ex;
    int ndfs = -1;

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&ex);

    for (ASocket *s : read) {
      FD_SET(s->_sock, &rd);
#ifdef __linux__
      ndfs = (ndfs < s->_sock ? s->_sock : ndfs);
#endif
    }

    for (ASocket *s : write) {
      FD_SET(s->_sock, &wr);
#ifdef __linux__
      ndfs = (ndfs < s->_sock ? s->_sock : ndfs);
#endif
    }

    for (ASocket *s : exept) {
      FD_SET(s->_sock, &ex);
#ifdef __linux__
      ndfs = (ndfs < s->_sock ? s->_sock : ndfs);
#endif
    }

    ++ndfs;

    ret = ::select(ndfs, &rd, &wr, &ex, timeout);

    read.remove_if([&rd](ASocket *s) { return FD_ISSET(s->_sock, &rd); });
    read.remove_if([&wr](ASocket *s) { return FD_ISSET(s->_sock, &wr); });
    read.remove_if([&ex](ASocket *s) { return FD_ISSET(s->_sock, &ex); });
    return ret;
  }

  int ASocket::getaddrinfo(const char * node, const char * service, addrinfo const * hints, addrinfo ** res)
  {
    int ret = 0;

    ret = ::getaddrinfo(node, service, hints, res);
    //implement better error handling.
    return ret;
  }

  int ASocket::getaddrinfo(std::string const & node, std::string const & service, addrinfo const * hints, addrinfo ** res)
  {
    int ret = 0;
    ret = ::getaddrinfo(node.c_str(), service.c_str(), hints, res);
    //implement better error handling.
    return ret;
  }

  void ASocket::freeaddrinfo(addrinfo * res)
  {
    ::freeaddrinfo(res);
  }

  ASocket::ASocket(int domain, int type, int proto):
    _dom(domain), _type(type), _proto(proto)
  {
#ifdef __linux__
    _sock = -1;
#else
    _sock = INVALID_SOCKET;
#endif
  }
} // namespace network
