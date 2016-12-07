/*
** ASocket.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Mon Nov 28 15:31:01 2016 Gabriel CADET
** Last update Wed Dec 07 20:21:19 2016 Gabriel CADET
*/

#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#ifdef __linux__
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
typedef int t_socket;
#else
# ifndef _WIN32
#  define _WIN32
#endif
# include <Winsock2.h>
# include <ws2tcpip.h>

# pragma comment(lib, "Ws2_32.lib")

typedef SOCKET t_socket;
typedef int ssize_t;
#endif

#include <string>
#include <list>

namespace network {
  /**
  ** \brief Base class for all others sockets.
  **
  */
  class ASocket {
    public:
      /**
      ** \brief Generic enum describing shutdown() flags.
      */
      enum How {
        SD_RCV, /**< Closing data input */
        SD_SND, /**< Closing data output */
        SD_ALL /**< Closing both input and output */
      };

    public:
      /**
      ** \brief Basic destructor for ASocket.
      */
      virtual ~ASocket() {};

      /**
      ** \brief The recv function receives data from a connected socket or a bound connectionless socket.
      **
      ** \param [out] buf pointer to the memory in which received data will be written.
      ** \param [in] len size of the data buffer.
      ** \param [in] flags set of flags to change function behavior.
      ** \return If no error occurs, recv returns the number of bytes received and the buffer pointed to by the buf parameter will contain this data received. If the connection has been gracefully closed, the return value is zero.
      */
      virtual ssize_t	recv(void *buf, size_t len, int flags = 0) = 0;
      virtual ssize_t	recv(std::string &buf, size_t len, int flags = 0) = 0;

      /**
      ** \brief The send function sends data on a connected socket.
      **
      ** \param [in] buf pointer to the memory containing the data to be sent.
      ** \param [in] len size of the data buffer.
      ** \param [in] flags set of flags to change function behavior.
      ** \return If no error occurs, send returns the total number of bytes sent, which can be less than the number requested to be sent in the len parameter.
      */
      virtual ssize_t	send(void *buf, size_t len, int flags = 0) = 0;
      virtual ssize_t send(std::string const &buf, int flags = 0) = 0;

      /**
      ** \brief The recvfrom function receives a datagram and stores the source address.
      **
      ** \param [out] buf pointer to the memory in which received data will be written.
      ** \param [in] len size of the data buffer.
      ** \param [in] flags set of flags to change function behavior.
      ** \param [out] src An optional pointer to a buffer in a sockaddr structure that will hold the source address upon return
      ** \param [in, out] srclen An optional pointer to the size, in bytes, of the buffer pointed to by the from parameter.
      ** \return If no error occurs, recvfrom returns the number of bytes received. If the connection has been gracefully closed, the return value is zero.
      */
      virtual ssize_t	recvFrom(void *buf, size_t len, int flags, sockaddr *src, int *srclen) = 0;
      virtual ssize_t	recvFrom(void *buf, size_t len, int flags, std::string &node, std::string &service) = 0;
      virtual ssize_t	recvFrom(std::string &buf, size_t len, int flags, sockaddr *src, int *srclen) = 0;
      virtual ssize_t	recvFrom(std::string &buf, size_t len, int flags, std::string &node, std::string &service) = 0;

      /**
      ** \brief The sendto function sends data to a specific destination.
      **
      ** \param [in] buf pointer to the memory containing data to be sent.
      ** \param [in] len size of the data buffer.
      ** \param [in] flags set of flags to change function behavior.
      ** \param [in] dest An optional pointer to a buffer in a sockaddr structure that will hold the source address upon return
      ** \param [in] destlen An optional pointer to the size, in bytes, of the buffer pointed to by the from parameter.
      ** \return If no error occurs, sendto returns the total number of bytes sent, which can be less than the number indicated by len.
      */
      virtual ssize_t	sendTo(void *buf, size_t len, int flags, const sockaddr *dest, int destlen) = 0;
      virtual ssize_t	sendTo(void *buf, size_t len, int flags, std::string const & dest, std::string const &service) = 0;
      virtual ssize_t	sendTo(std::string &buf, int flags, const sockaddr *dest, int destlen) = 0;
      virtual ssize_t	sendTo(std::string &buf, int flags, std::string const & dest, std::string const &service) = 0;

      /**
      ** \brief The bind function associates a local address with a socket.
      **
      ** \param [in] addr A pointer to a sockaddr structure of the local address to assign to the bound socket .
      ** \param [in] addrlen The length, in bytes, of the value pointed to by the name parameter.
      ** \return If no error occurs, bind returns zero.
      */
      virtual int	bind(const sockaddr *addr, int addrlen) = 0;
      virtual int	bind(std::string const &addr, std::string const &service) = 0;

      /**
      ** \brief The listen function places a socket in a state in which it is listening for an incoming connection.
      **
      ** \param [in] backlog The maximum length of the queue of pending connections.
      ** \return If no error occurs, listen returns zero.
      */
      virtual int	listen(int backlog) = 0;

      /**
      ** \brief The accept function permits an incoming connection attempt on a socket.
      **
      ** \param [out] addr An optional pointer to a buffer that receives the address of the connecting entity, as known to the communications layer.
      ** \param [in, out] addrlen An optional pointer to an integer that contains the length of structure pointed to by the addr parameter.
      ** \return If no error occurs, accept returns a pointer on a new ASocket instance, that contains the handler for the socket on wich the actual connection is made.
      */
      virtual ASocket	*accept(sockaddr *addr, int *addrlen) = 0;
      virtual ASocket *accept(std::string const &addr, std::string const &service) = 0;

      /**
      ** \brief The connect function establishes a connection to a specified socket.
      **
      ** \param [in] addr A pointer to the sockaddr structure to which the connection should be established.
      ** \param [in] addrlen The length, in bytes, of the sockaddr structure pointed to by the name parameter.
      ** \return If no error occurs, connect returns zero.
      */
      virtual int	connect(sockaddr const *addr, int addrlen) = 0;
      virtual int	connect(std::string const &addr, std::string const &service) = 0;

      /**
      ** \brief The shutdown function disables sends or receives on a socket.
      **
      ** \param [in] flgs A flag that describes what types of operation will no longer be allowed.
      ** \return If no error occurs, shutdown returns zero.
      */
      virtual int	shutdown(How flgs);

    public: //class functions
      /**
      ** \brief The select function determines the status of one or more sockets, waiting if necessary, to perform synchronous I/O.
      **
      ** \param [in, out] read A list of pointer to ASocket to be checked for readability
      ** \param [in, out] write A list of pointer to ASocket to be checked for writability
      ** \param [in, out] exept A list of pointer to ASocket to be checked for errors
      ** \param [in] timeout the maximum time for select to wait. NULL for blocking op.
      ** \return select return the total number of socket in the updated lists, 0 if a timeout occured, or -1 if an error occured.
      */
      virtual int select(std::list<ASocket *> &read, std::list<ASocket *> &write, std::list<ASocket *> &exept, timeval *timeout);

      /**
      ** \brief The getaddrinfo function provides protocol-independent translation from an ANSI host name to an address.
      **
      ** \param [in] node A pointer to a NULL-terminated ANSI string that contains a host (node) name or a numeric host address string.
      ** \param [in] service A pointer to a NULL-terminated ANSI string that contains either a service name or port number represented as a string.
      ** \param [in] hints A pointer to an addrinfo structure that provides hints about the type of socket the caller supports.
      ** \param [out] res A pointer to a linked list of one or more addrinfo structures that contains response information about the host.
      ** \return Success returns zero. Failure returns a nonzero Sockets error code.
      */
      static int getaddrinfo(const char *node, const char *service, addrinfo const *hints, addrinfo **res);
      /**
      ** \overload
      ** \param [in] node A reference to a string containing either a hostname, or a numeric host address.
      ** \param [in] service A reference to a string containing either a hostname, or a numeric host address.
      ** \param [in] hints A pointer to an addrinfo structure that provides hints about the type of socket the caller supports.
      ** \param [out] res A pointer to a linked list of one or more addrinfo structures that contains response information about the host.
      ** \return Success returns zero. Failure returns a nonzero Sockets error code.
      */
      static int getaddrinfo(std::string const &node, std::string const &service, addrinfo const *hints, addrinfo **res);

      /**
      ** \brief The freeaddrinfo function frees address information that the getaddrinfo function dynamically allocates in addrinfo structures.
      **
      ** \param [in] res A pointer to the addrinfo structure or linked list of addrinfo structures to be freed. All dynamic storage pointed to within the addrinfo structure or structures is also freed.
      ** \return This function does not return any value.
      */
      static void freeaddrinfo(addrinfo *res);

    protected:
      ASocket(int dom, int type, int proto);
      ASocket(t_socket sock, int dom, int type, int proto) :
        _sock(sock), _dom(dom), _type(type), _proto(proto)
      {}

      t_socket	_sock; /**< Socket handler. Must be instantiated in subclases constructor */
      int       _dom;
      int       _type;
      int       _proto;

#ifdef _WIN32
      static int	nbSock;
      static WSADATA	wsaData;
#endif
  };
} // namespace network

#endif /* !ASOCKET_HPP_ */
