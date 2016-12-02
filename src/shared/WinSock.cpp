/* ** WinSock.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 14:55:13 2016 Gabriel CADET
** Last update Tue Nov 29 15:04:36 2016 Gabriel CADET
*/

#include "WinSock.hpp"
#include <iostream>

namespace network {
  int WinSock::nbSock = 0;
  WSADATA WinSock::wsaData;

  WinSock::WinSock(int domain, int type, int protocol)
  :ASocket(domain, type, protocol)
  {
    if (nbSock == 0) {
      int res;
      res = WSAStartup(MAKEWORD(2,2), &wsaData);
      if (res != 0)
        throw;
    }
    _sock = socket(domain, type, protocol);
    if (_sock == INVALID_SOCKET)
      throw;
	  ++nbSock;
  }

  WinSock::WinSock(t_socket sock, int domain, int type, int prot) :
    ASocket(sock, domain, type, prot)
  {
    ++nbSock;
  }

  WinSock::~WinSock() {
    closesocket(_sock);
    --nbSock;
    if (nbSock <= 0)
      WSACleanup();
  }

  ssize_t WinSock::recv(void * buf, size_t len, int flag)
  {
    int ret;
    DWORD rcvBytes;
    DWORD flags = flag;
    WSABUF  data;

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSARecv(_sock, &data, 1, &rcvBytes, &flags, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;

    return rcvBytes;
  }

  ssize_t WinSock::recv(std::string & buf, size_t len, int flag)
  {
    WSABUF  data;
    DWORD   flags = flag;
    DWORD   rcvBytes;
    int     ret;

    data.len = len;
    data.buf = new char[len + 1];

    ret = ::WSARecv(_sock, &data, 1, &rcvBytes, &flags, NULL, NULL);
    if (ret == SOCKET_ERROR) {
      delete[] data.buf;
      return -1;
    }
    data.buf[rcvBytes] = 0;
    buf.assign(data.buf);
    delete[] data.buf;
    return rcvBytes;
  }

  ssize_t WinSock::send(void * buf, size_t len, int flag)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSASend(_sock, &data, 1, &sndBytes, flags, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;

    return sndBytes;
  }

  ssize_t WinSock::send(std::string const & buf, int flag)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;

    data.len = buf.length();
    data.buf = new char[buf.length() + 1];

    std::copy(buf.begin(), buf.end(), data.buf);
    ret = ::WSASend(_sock, &data, 1, &sndBytes, flags, NULL, NULL);
    delete[] data.buf;
    if (ret == SOCKET_ERROR)
      return -1;

    return sndBytes;
  }

  ssize_t WinSock::recvFrom(void * buf, size_t len, int flag, sockaddr * src, int *addrlen)
  {
    int     ret;
    DWORD   rcvBytes;
    WSABUF  data;
    DWORD   flags = flag;

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSARecvFrom(_sock, &data, 1, &rcvBytes, &flags, src, addrlen, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;

    return rcvBytes;
  }

  ssize_t WinSock::recvFrom(void * buf, size_t len, int flag, std::string & node, std::string & service)
  {
    int     ret;
    sockaddr_in src;
    int         addrlen = sizeof(src);

    ret = this->recvFrom(buf, len, flag, reinterpret_cast<sockaddr *>(&src), &addrlen);
    if (ret == -1)
      return -1;

    char    hostname[NI_MAXHOST];
    char    servname[NI_MAXSERV];
    if (::getnameinfo(reinterpret_cast<sockaddr *>(&src), addrlen, hostname, NI_MAXHOST, servname, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV))
      return -1;

    node.assign(hostname);
    service.assign(servname);
    return ret;
  }

  ssize_t WinSock::recvFrom(std::string & buf, size_t len, int flag, sockaddr * src, int *addrlen)
  {
    int     ret;
    char    *cbuf;

    cbuf = new char[len + 1];

    ret = this->recvFrom(cbuf, len, flag, src, addrlen);
    if (ret == -1) {
      delete[] cbuf;
      return -1;
    }
    cbuf[ret] = 0;

    buf.assign(cbuf);
    delete[] cbuf;

    return ret;
  }

  ssize_t WinSock::recvFrom(std::string & buf, size_t len, int flag, std::string & node, std::string & service)
  {
    int     ret;
    char    *cbuf;

    cbuf = new char[len + 1];

    ret = this->recvFrom(cbuf, len, flag, node, service);
    if (ret == -1) {
      std::cout << WSAGetLastError() << std::endl;
      delete[] cbuf;
      return -1;
    }
    cbuf[ret] = 0;

    buf.assign(cbuf);
    delete[] cbuf;

    return ret;
  }

  ssize_t WinSock::sendTo(void * buf, size_t len, int flag, const sockaddr * dest, int addrlen)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSASendTo(_sock, &data, 1, &sndBytes, flags, dest, addrlen, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;

    return sndBytes;
  }

  ssize_t WinSock::sendTo(void * buf, size_t len, int flag, std::string const & dest, std::string const & service)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;
    addrinfo  hints;
    addrinfo  *destinfo;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    ASocket::getaddrinfo(dest, service, &hints, &destinfo);

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSASendTo(_sock, &data, 1, &sndBytes, flags, destinfo->ai_addr , destinfo->ai_addrlen, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR)
      return -1;

    return sndBytes;
  }

  ssize_t WinSock::sendTo(std::string & buf, int flag, const sockaddr * dest, int destlen)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;

    data.len = buf.length();
    data.buf = new char[buf.length() + 1];

    std::copy(buf.begin(), buf.end(), data.buf);
    ret = ::WSASendTo(_sock, &data, 1, &sndBytes, flags, dest, destlen, NULL, NULL);
    delete[] data.buf;
    if (ret == SOCKET_ERROR) {
      return -1;
    }

    return sndBytes;
  }

  ssize_t WinSock::sendTo(std::string & buf, int flag, std::string const & dest, std::string const & service)
  {
    int     ret;
    DWORD   sndBytes;
    DWORD   flags = flag;
    WSABUF  data;
    addrinfo  hints;
    addrinfo  *destinfo;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    ASocket::getaddrinfo(dest, service, &hints, &destinfo);

    data.len = buf.length();
    data.buf = new char[buf.length() + 1];

    std::copy(buf.begin(), buf.end(), data.buf);
    ret = ::WSASendTo(_sock, &data, 1, &sndBytes, flags, destinfo->ai_addr, destinfo->ai_addrlen, NULL, NULL);
    delete[] data.buf;
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR) {
      return -1;
    }

    return sndBytes;
  }

  int     WinSock::bind(const sockaddr * addr, int addrlen)
  {
    int   ret;
    ret = ::bind(_sock, addr, addrlen);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  int WinSock::bind(std::string const & addr, std::string const & service)
  {
    int ret;
    addrinfo  hints;
    addrinfo  *destinfo;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    getaddrinfo(addr, service, &hints, &destinfo);

    ret = ::bind(_sock, destinfo->ai_addr, destinfo->ai_addrlen);
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR)
      return -1;

    return ret;
  }

  int     WinSock::listen(int backlog)
  {
    int ret;

    ret = ::listen(_sock, backlog);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  ASocket *WinSock::accept(sockaddr * addr, int * addrlen)
  {
    SOCKET nsock = ::WSAAccept(_sock, addr, addrlen, NULL, NULL);

    if (nsock == INVALID_SOCKET)
      return 0;

    WinSock *ret = new WinSock(nsock, _dom, _type, _proto);
    return ret;
  }

  ASocket * WinSock::accept(std::string const & addr, std::string const & service)
  {
    SOCKET    nsock;
    addrinfo  hints;
    addrinfo  *destinfo;
    int       addrlen;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    ASocket::getaddrinfo(addr, service, &hints, &destinfo);
    addrlen = destinfo->ai_addrlen;

    nsock = ::WSAAccept(_sock, destinfo->ai_addr, &addrlen, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (nsock == INVALID_SOCKET)
      return NULL;
    WinSock *ret = new WinSock(nsock, _dom, _type, _proto);
    return ret;
  }

  int WinSock::connect(sockaddr const * addr, int addrlen)
  {
    int ret;

    ret = ::WSAConnect(_sock, addr, addrlen, NULL, NULL, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  int WinSock::connect(std::string const & addr, std::string const & service)
  {
    int ret;
    addrinfo  hints;
    addrinfo  *destinfo;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    ASocket::getaddrinfo(addr, service, &hints, &destinfo);
    ret = ::WSAConnect(_sock, destinfo->ai_addr, destinfo->ai_addrlen, NULL, NULL, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR)
      return -1;

    return ret;
  }
} // namespace network
