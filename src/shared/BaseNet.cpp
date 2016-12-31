/*
** BaseNet.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Mon Dec 19 23:42:11 2016 Gabriel CADET
** Last update Sat Dec 31 14:26:44 2016 Gabriel CADET
*/

#include "BaseNet.hpp"

namespace entity_component_system::system {
  std::mutex	BaseNet::actionLock;
  std::list<BaseNet::pendingAction>	BaseNet::actionList;
  std::map<ecs::ID<ecs::Entity>, ecs::ID<ecs::Entity>>	BaseNet::_relation_id;

  void	BaseNet::makeNetAction(BaseNet::targetSystem service, netAction act, char *data) {
    std::lock_guard<std::mutex>	lock(actionLock);
    actionList.push_back(pendingAction({service, act, data}));
  }

  void	BaseNet::getNetAction(BaseNet::targetSystem service, std::list<pendingAction> &dest) {
    std::lock_guard<std::mutex>	lock(actionLock);
    auto	it = actionList.begin();

    while ((it = std::find_if(actionList.begin(), actionList.end(), [&service](std::tuple<targetSystem, netAction, void *> const &elm){ return std::get<0>(elm) == service; } )) != actionList.end()) {
      dest.splice(dest.begin(), actionList, it);
    }

  }
}
