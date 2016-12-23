/*
** BaseNet.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Mon Dec 19 23:42:11 2016 Gabriel CADET
** Last update Tue Dec 20 01:24:13 2016 Gabriel CADET
*/

#include "BaseNet.hpp"

namespace ecs::system {
  void	BaseNet::makeNetAction(BaseNet::targetSystem service, netAction act, void *data) {
    std::lock_guard<std::mutex>	lock(actionLock);
    actionList.push_back(std::tuple<targetSystem, netAction, void *>({service, act, data}));
  }

  void	BaseNet::getNetAction(BaseNet::targetSystem service, std::list<std::tuple<targetSystem, netAction, void *>> &dest) {
    std::lock_guard<std::mutex>	lock(actionLock);
    auto	it = actionList.begin();

    while ((it = std::find_if(actionList.begin(), actionList.end(), [&service](std::tuple<targetSystem, netAction, void *> const &elm){ return std::get<0>(elm) == service; } )) != actionList.end()) {
      dest.splice(dest.begin(), actionList, it);
    }

  }
}
