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
#include <algorithm>

namespace network {
  class WinSock : public ASocket {
    public:
      WinSock(int domain, int type, int protocol);
      WinSock(t_socket sock, int domain, int type, int protocol);
      WinSock(WinSock const &) = delete;
      virtual ~WinSock();

      WinSock &operator=(WinSock const &) = delete;

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
      virtual ASocket *accept(std::string const &addr, std::string const &service);

      virtual int	connect(sockaddr const *addr, int addrlen);
      virtual int	connect(std::string const &addr, std::string const &service);

    private:
      static int	nbSock;
      static WSADATA	wsaData;
  };

  class WinTCPSock : public WinSock {
    public:
      WinTCPSock() : WinSock(AF_INET, SOCK_STREAM, IPPROTO_TCP) {}
      ~WinTCPSock() {}
      WinTCPSock(WinTCPSock const &) = delete;
      WinTCPSock & operator=(WinTCPSock const &) = delete;
  };

  class WinUDPSock : public WinSock {
    public:
      WinUDPSock() : WinSock(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {}
      ~WinUDPSock() {}
      WinUDPSock(WinUDPSock const &) = delete;
      WinUDPSock & operator=(WinUDPSock const &) = delete;
  };
} // namespace network
#endif /* !WINSOCK_HPP_ */
