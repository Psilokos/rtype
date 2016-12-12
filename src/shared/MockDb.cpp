#include "MockDb.hpp"

namespace ecs::database {
  int	Component::id = 0;
  int	Entity::id = 0;

  Component::Component() : _id(id++) {}
  Component::Component(Component const &src) : _id(id++)
  {
    for (auto &pr : src._attr)
      _attr[pr.first] = "";
  }

  Component::Component(std::vector<std::string> const &&attr) : _id(id++)
  {
    for (auto atN : attr)
      _attr[atN] = "";
  }

  Entity::Entity() : _id(id++) {}

  int		Entity::addComponent(std::string const &cname, Component *cmp) {
    _components[cname] = cmp;
    return 0;
  }

  Component *Entity::getComponent(std::string const &cname) {
    return _components[cname];
  }


  Entity	*IDataBase::getEntityById(int id) {
    return (_entities[id]);
  }

  int		IDataBase::addEntity() {
    int		id;
    Entity	*newEnt = new Entity;

    id = newEnt->getId();

    _entities[id] = newEnt;
    return id;
  }

  void		IDataBase::removeEntity(int eid){
    Entity	*ent;
    int		cid;

    ent = _entities[eid];
    for (auto cmp : ent->_components) {
      decltype(_map.begin())	it;

      cid = cmp.second->getId();
      it = std::find<decltype(_map.begin())>(_map.begin(), _map.end(), std::pair<int, int>({eid, cid}));

      if (it != _map.end())
        _map.erase(it);

      if (_components.find(cid) != _components.end())
        _components.erase(_components.find(cid));

      delete cmp.second;
    }

    if (_entities.find(eid) != _entities.end())
      _entities.erase(_entities.find(eid));
  }

  int		IDataBase::bindComponent(std::string const &Cname, Component *cmp, int entId) {
    int		cmpId;

    cmpId = cmp->getId();
    _components[cmpId] = cmp;
    _cname[cmpId] = Cname;
    _entities.at(entId)->addComponent(Cname, cmp);
    _map.push_back({entId, cmpId});
    return 0;
  }

  std::vector<Entity *>		IDataBase::getEntitiesWithComponents(std::string const &cname) {
    std::vector<Entity *>	ret;
    int				cid;
    int				eid;

    for (auto cmpnents : _cname) {
      if (cmpnents.second == cname) {
        cid = cmpnents.first;
        for (auto mp : _map)
          if (mp.second == cid)
            ret.push_back(_entities.at(mp.first));
      }
    }
    return ret;
  }
} // namespace ecs::database
