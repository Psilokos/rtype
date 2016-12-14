/*
** BaseNet.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 09 16:26:34 2016 Gabriel CADET
** Last update Wed Dec 14 15:44:33 2016 Gabriel CADET
*/

#ifndef BASENET_HPP_
#define BASENET_HPP_

#include "ISystem.hpp"

namespace ecs::system {
  class BaseNet : public ISystem {
    public:
      struct request {
        unsigned char	rc;
        unsigned short	sz;
        char		data[0];
      } __attribute__((__packed__));

      struct ecsData {
        unsigned int	eid;
        unsigned int	cid;
        char		data[0];
      };

    protected:
      static short const	netBufSize = 512;
      static short const	reqHeadSize = sizeof(unsigned char) + sizeof(unsigned short);
  };
}
#endif /* !BASENET_HPP_ */
