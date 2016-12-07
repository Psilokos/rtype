/*
** ISystem.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 19:37:59 2016 Gabriel CADET
** Last update Wed Dec 07 19:40:18 2016 Gabriel CADET
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "IDataBase.hpp"

namespace ecs::system {
  class ISystem {
    public:
      ~ISystem() {}

      void	update(ecs::database::IDataBase &) = 0;
  };
} // namespace ecs::system
#endif /* !ISYSTEM_HPP_ */
