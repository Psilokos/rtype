/*
** WinSock.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 14:42:42 2016 Gabriel CADET
** Last update Fri Dec 02 19:35:01 2016 Gabriel CADET
*/

#ifndef WINSOCK_HPP_
#define WINSOCK_HPP_

#include "ASocket.hpp"
#include <algorithm>

namespace network {
  template<int dom, int type, int proto>
  class Socket : public ASocket {
    public:
      Socket() : ASocket(dom, type, proto)
      {
        if (ASocket::nbSock == 0) {
          int res;
          res = ::WSAStartup(MAKEWORD(2,2), &ASocket::wsaData);
          if (res != 0)
            throw;
        }
        _sock = socket(dom, type, proto);
        if (_sock == INVALID_SOCKET)
          throw;
        ++ASocket::nbSock;
      }

      Socket(t_socket sock) : ASocket(sock, domain, type, prot)
      {
        ++ASocket::nbSock;
      }

      Socket(Socket const &) = delete;

      virtual ~Socket() {
        closesocket(_sock);
        --ASocket::nbSock;
        if (ASocket::nbSock <= 0)
          ::WSACleanup();
      }

      Socket &operator=(Socket const &) = delete;

      virtual ssize_t recv(void *buf, size_t len, int flag = 0);
      virtual ssize_t	recv(std::string &buf, size_t len, int flags = 0);

      virtual ssize_t send(void *buf, size_t len, int flag = 0);
      virtual ssize_t send(std::string const &buf, int flags = 0);


      virtual ssize_t	recvFrom(void *buf, size_t len, int flags, sockaddr *src, int *addrlen);
      virtual ssize_t	recvFrom(void *buf, size_t len, int flags, std::string &node, std::string &service);
      virtual ssize_t	recvFrom(std::string &buf, size_t len, int flags, sockaddr *src, int *srclen);
      virtual ssize_t	recvFrom(std::string &buf, size_t len, int flags, std::string &node, std::string &service);

      virtual ssize_t	sendTo(void *buf, size_t len, int flags, const sockaddr *dest, int addrlen);
      virtual ssize_t	sendTo(void *buf, size_t len, int flags, std::string const & dest, std::string const &service);
      virtual ssize_t	sendTo(std::string &buf, int flags, const sockaddr *dest, int destlen);
      virtual ssize_t	sendTo(std::string &buf, int flags, std::string const & dest, std::string const &service);

      virtual int	bind(const sockaddr *addr, int addrlen);
      virtual int	bind(std::string const &addr, std::string const &service);

      virtual int	listen(int backlog);

      virtual ASocket	*accept(sockaddr *addr, int *addrlen);
      virtual ASocket	*accept(std::string const &addr, std::string const &service);

      virtual int	connect(sockaddr const *addr, int addrlen);
      virtual int	connect(std::string const &addr, std::string const &service);

  };

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recv(void * buf, size_t len, int flag)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recv(std::string & buf, size_t len, int flag)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::send(void * buf, size_t len, int flag)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::send(std::string const & buf, int flag)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recvFrom(void * buf, size_t len, int flag, sockaddr * src, int *addrlen)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recvFrom(void * buf, size_t len, int flag, std::string & node, std::string & service)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recvFrom(std::string & buf, size_t len, int flag, sockaddr * src, int *addrlen)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::recvFrom(std::string & buf, size_t len, int flag, std::string & node, std::string & service)
  {
    int     ret;
    char    *cbuf;

    cbuf = new char[len + 1];

    ret = this->recvFrom(cbuf, len, flag, node, service);
    if (ret == -1) {
      delete[] cbuf;
      return -1;
    }
    cbuf[ret] = 0;

    buf.assign(cbuf);
    delete[] cbuf;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::sendTo(void * buf, size_t len, int flag, const sockaddr * dest, int addrlen)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::sendTo(void * buf, size_t len, int flag, std::string const & dest, std::string const & service)
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

    if (0 != ASocket::getaddrinfo(dest, service, &hints, &destinfo))
      return -1;

    data.len = len;
    data.buf = reinterpret_cast<char *>(buf);

    ret = ::WSASendTo(_sock, &data, 1, &sndBytes, flags, destinfo->ai_addr , destinfo->ai_addrlen, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR)
      return -1;

    return sndBytes;
  }

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::sendTo(std::string & buf, int flag, const sockaddr * dest, int destlen)
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

  template<int dom, int type, int proto>
  ssize_t Socket<dom, type, proto>::sendTo(std::string & buf, int flag, std::string const & dest, std::string const & service)
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

  template<int dom, int type, int proto>
  int     Socket<dom, type, proto>::bind(const sockaddr * addr, int addrlen)
  {
    int   ret;
    ret = ::bind(_sock, addr, addrlen);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  int Socket<dom, type, proto>::bind(std::string const & addr, std::string const & service)
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

  template<int dom, int type, int proto>
  int     Socket<dom, type, proto>::listen(int backlog)
  {
    static_assert(proto != IPPROTO_UDP, "Cannot call accept on UDP Socket.");
    static_assert(type != SOCK_DGRAM, "Cannot call accept on connectionless Sockets." );
    int ret;

    ret = ::listen(_sock, backlog);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  ASocket *Socket<dom, type, proto>::accept(sockaddr * addr, int * addrlen)
  {
    static_assert(proto != IPPROTO_UDP, "Cannot call accept on UDP Socket.");
    static_assert(type != SOCK_DGRAM, "Cannot call accept on connectionless Sockets." );

    SOCKET nsock = ::WSAAccept(_sock, addr, addrlen, NULL, NULL);

    if (nsock == INVALID_SOCKET)
      return 0;

    Socket<dom, type, proto> *ret = new Socket<dom, type, proto>(nsock);
    return ret;
  }

  template<int dom, int type, int proto>
  ASocket * Socket<dom, type, proto>::accept(std::string const & addr, std::string const & service)
  {
    static_assert(proto != IPPROTO_UDP, "Cannot call accept on UDP Socket.");
    static_assert(type != SOCK_DGRAM, "Cannot call accept on connectionless Sockets." );

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

    if (0 != ASocket::getaddrinfo(addr, service, &hints, &destinfo))
      return NULL;
    addrlen = destinfo->ai_addrlen;

    nsock = ::WSAAccept(_sock, destinfo->ai_addr, &addrlen, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (nsock == INVALID_SOCKET)
      return NULL;
    Socket<dom, type, proto> *ret = new Socket<dom, type, proto>(nsock, _dom, _type, _proto);
    return ret;
  }

  template<int dom, int type, int proto>
  int Socket<dom, type, proto>::connect(sockaddr const * addr, int addrlen)
  {
    int ret;

    ret = ::WSAConnect(_sock, addr, addrlen, NULL, NULL, NULL, NULL);
    if (ret == SOCKET_ERROR)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  int Socket<dom, type, proto>::connect(std::string const & addr, std::string const & service)
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

    if (0 != ASocket::getaddrinfo(addr, service, &hints, &destinfo))
      return -1;
    ret = ::WSAConnect(_sock, destinfo->ai_addr, destinfo->ai_addrlen, NULL, NULL, NULL, NULL);
    ASocket::freeaddrinfo(destinfo);
    if (ret == SOCKET_ERROR)
      return -1;

    return ret;
  }

  typedef Socket<AF_INET, SOCK_STREAM, IPPROTO_TCP> TcpSocket;
  typedef Socket<AF_INET, SOCK_DGRAM, IPPROTO_UDP> UdpSocket;
} // namespace network
#endif /* !WINSOCK_HPP_ */
