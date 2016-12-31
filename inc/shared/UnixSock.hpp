/*
** UnixSock.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 02 14:09:53 2016 Gabriel CADET
** Last update Fri Dec 30 16:35:57 2016 Gabriel CADET
*/

#ifndef UNIXSOCK_HPP_
#define UNIXSOCK_HPP_

#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <memory>
#include "ASocket.hpp"

namespace network {

  template<int dom, int type, int proto>
  class Socket : public ASocket {
    public:
      Socket() : ASocket(dom, type, proto)
      {
        _sock = socket(dom, type, proto);
        if (_sock == -1)
          throw;
      }

      Socket(t_socket sock) : ASocket(sock, dom, type, proto)
      {}

      Socket(Socket const &) = delete;
      virtual ~Socket() {
        close(_sock);
      }

      Socket		&operator=(Socket const &) = delete;

      virtual ssize_t	recv(void *buf, size_t len, int flag = 0);
      virtual ssize_t	recv(std::string &buf, size_t len, int flags = 0);

      virtual ssize_t	send(void *buf, size_t len, int flag = 0);
      virtual ssize_t	send(std::string const &buf, int flags = 0);

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
  ASocket	*Socket<dom, type, proto>::accept(sockaddr *addr, int *addrlen) {
    if (proto == IPPROTO_UDP || type == SOCK_DGRAM)
      throw ; //specify exception here please
    socklen_t	alen;
    alen = *addrlen;
    t_socket	nsock = ::accept(_sock, addr, &alen);

    *addrlen = alen;

    if (nsock == -1)
      return NULL;

    Socket<dom, type, proto> *ret = new Socket<dom, type, proto>(nsock);
    return ret;
  }

  template<int dom, int type, int proto>
  int		Socket<dom, type, proto>::listen(int backlog) {
    if (proto == IPPROTO_UDP || type == SOCK_DGRAM)
      throw ; //specify exception here please

    int		ret;

    ret = ::listen(_sock, backlog);
    if (ret == -1)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::recv(void *buf, size_t len, int flag) {
    ssize_t	ret;

    ret = ::recv(_sock, buf, len, flag);
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::recv(std::string &buf, size_t len, int flag) {
    char	*cbuf;
    int		ret;

    cbuf = new char[len + 1];
    ret = this->recv(cbuf, len, flag);
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
  ssize_t	Socket<dom, type, proto>::send(void *buf, size_t len, int flag) {
    int		ret;

    ret = ::send(_sock, buf, len, flag);
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::send(std::string const &buf, int flag) {
    int		ret;
    char	*cbuf;

    cbuf = new char[buf.length() + 1];
    std::copy(buf.begin(), buf.end(), cbuf);

    ret = this->send(cbuf, buf.length(), flag);
    delete[] cbuf;
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::recvFrom(void *buf, size_t len, int flag, sockaddr *src, int *addr) {
    ssize_t	ret;
    socklen_t	addrlen = *addr;

    ret = ::recvfrom(_sock, buf, len, flag, src, &addrlen);
    *addr = addrlen;
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::recvFrom(std::string &buf, size_t len, int flag, sockaddr *src, int *addr) {
    int		ret;
    char	*cbuf;

    cbuf = new char[len + 1];

    ret = this->recvFrom(cbuf, len, flag, src, addr);
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
  ssize_t	Socket<dom, type, proto>::recvFrom(void *buf, size_t len, int flag, std::string &node, std::string &service) {
    int		ret;
    sockaddr_in	src;
    int		addrlen = sizeof(src);

    ret = this->recvFrom(buf, len, flag, reinterpret_cast<sockaddr *>(&src), &addrlen);
    if (ret == -1)
      return -1;

    char	hostname[NI_MAXHOST];
    char	servname[NI_MAXSERV];
    if (::getnameinfo(reinterpret_cast<sockaddr *>(&src), addrlen, hostname, NI_MAXHOST, servname, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV))
      return -1;

    node.assign(hostname);
    service.assign(servname);
    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::recvFrom(std::string &buf, size_t len, int flag, std::string &node, std::string &service) {
    int		ret;
    char	*cbuf;

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
  ssize_t	Socket<dom, type, proto>::sendTo(void *buf, size_t len, int flag, const sockaddr *dest, int addrlen) {
    int		ret;

    ret = ::sendto(_sock, buf, len, flag, dest, addrlen);
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::sendTo(void *buf, size_t len, int flag, std::string const &dest, std::string const &service) {
    int		ret;
    addrinfo	hints;
    addrinfo	*destinfo;

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

    ret = this->sendTo(buf, len, flag, destinfo->ai_addr, destinfo->ai_addrlen);
    ASocket::freeaddrinfo(destinfo);
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::sendTo(std::string &buf, int flag, const sockaddr *dest, int destlen) {
    int		ret;
    char	*cbuf;

    cbuf = new char[buf.length() + 1];

    std::copy(buf.begin(), buf.end(), cbuf);
    ret = this->sendTo(cbuf, buf.length(), flag, dest, destlen);
    delete[] cbuf;
    if (ret == -1) {
      return -1;
    }

    return ret;
  }

  template<int dom, int type, int proto>
  ssize_t	Socket<dom, type, proto>::sendTo(std::string &buf, int flag, std::string const &addr, std::string const &service) {
    int		ret;
    char	*cbuf;

    cbuf = new char[buf.length() + 1];

    ret = this->sendTo(cbuf, buf.length(), flag, addr, service);
    delete[] cbuf;
    if (ret == -1)
      return -1;

    return ret;
  }

  template<int dom, int type, int proto>
  int		Socket<dom, type, proto>::bind(const sockaddr *addr, int addrlen) {
    int		ret;

    ret = ::bind(_sock, addr, addrlen);
    if (ret == -1)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  int		Socket<dom, type, proto>::bind(std::string const &addr, std::string const &service) {
    int		ret;
    addrinfo	hints;
    addrinfo	*destinfo;

    hints.ai_flags = 0;
    hints.ai_family = _dom;
    hints.ai_socktype = _type;
    hints.ai_protocol = _proto;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    if (0 != getaddrinfo(addr, service, &hints, &destinfo))
      return -1;

    ret = this->bind(destinfo->ai_addr, destinfo->ai_addrlen);
    ASocket::freeaddrinfo(destinfo);
    if (ret == -1)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  ASocket	*Socket<dom, type, proto>::accept(std::string const &addr, std::string const &service) {
    if (proto == IPPROTO_UDP || type == SOCK_DGRAM)
      throw ; //specify exception here please
    addrinfo	hints;
    addrinfo	*destinfo;
    int		addrlen;
    ASocket	*ret;

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
    ret = this->accept(destinfo->ai_addr, &addrlen);
    ASocket::freeaddrinfo(destinfo);
    return ret;
  }

  template<int dom, int type, int proto>
  int		Socket<dom, type, proto>::connect(sockaddr const *addr, int addrlen) {
    socklen_t	alen;
    int		ret;

    alen = addrlen;
    ret = ::connect(_sock, addr, alen);
    if (ret == -1)
      return -1;
    return ret;
  }

  template<int dom, int type, int proto>
  int		Socket<dom, type, proto>::connect(std::string const &addr, std::string const &service) {
    int		ret;
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
    ret = this->connect(destinfo->ai_addr, destinfo->ai_addrlen);
    if (ret == -1)
      return -1;
    return ret;
  }

  typedef Socket<AF_INET, SOCK_STREAM, IPPROTO_TCP> TcpSocket;
  typedef Socket<AF_INET, SOCK_DGRAM, IPPROTO_UDP> UdpSocket;
} // namespace network
#endif /* !UNIXSOCK_HPP_ */
