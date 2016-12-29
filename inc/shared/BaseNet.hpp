/*
** BaseNet.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 09 16:26:34 2016 Gabriel CADET
** Last update Thu Dec 29 19:00:11 2016 Gabriel CADET
*/

#ifndef BASENET_HPP_
#define BASENET_HPP_

#include <list>
#include <tuple>
#include <mutex>

#include "ISystem.hpp"

namespace entity_component_system::system {
  class BaseNet : public ISystem {
    public:
      struct request {
        unsigned char	rc;
        unsigned short	sz;
        char		data[0];
      } __attribute__((__packed__));

      enum targetSystem {
        CONNECTION,
        TRANSMIT
      };

      enum netAction {
        DISCONNECT,
        CONNECT,
        MENU
      };

      typedef std::tuple<targetSystem, netAction, char *> pendingAction;

      static void	makeNetAction(targetSystem service, netAction act, char *data = nullptr);
      static void	getNetAction(targetSystem service, std::list<pendingAction> &dest);

    protected:
      static short const	netBufSize = 512;
      static short const	reqHeadSize = sizeof(unsigned char) + sizeof(unsigned short);

    private:
      static std::list<pendingAction>	actionList;
      static std::mutex			actionLock;
  };
}
#endif /* !BASENET_HPP_ */
