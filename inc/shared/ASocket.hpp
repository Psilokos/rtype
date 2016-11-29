/*
** ASocket.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Mon Nov 28 15:31:01 2016 Gabriel CADET
** Last update Tue Nov 29 14:42:04 2016 Gabriel CADET
*/

#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#ifdef __linux__
# include <sys/socket.h>
typedef int t_socket;
#else
# include <Winsock2.h>
typedef SOCKET t_socket;
#endif

namespace network {
  class ASocket {
    public:
      enum How {
        SD_RCV,
        SD_SND,
        SD_ALL
      };

    public:
      virtual ssize_t	recv(void *buf, size_t len, int flags = 0) = 0;
      virtual ssize_t	send(void *buf, size_t len, int flags = 0) = 0;
      virtual ssize_t	recvFrom(void *buf, size_t len, int flags, sockaddr *src, int addrlen) = 0;
      virtual ssize_t	sendTo(void *buf, size_t len, int flags, const sockaddr *dest, int addrlen) = 0;
      virtual int	bind(const sockaddr *addr, int addrlen) = 0;
      virtual int	listen(int backlog) = 0;
      virtual t_socket	accept(sockaddr *addr, int *addrlen) = 0;
      virtual int	shutdown(How flgs) = 0;

    protected:
      ASocket();
      virtual ~ASocket();

      t_socket	_sock;

  };
} // namespace network

#endif /* !ASOCKET_HPP_ */
