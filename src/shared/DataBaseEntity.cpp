//
// Entity.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 13:36:34 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 21:29:10 2016 Victorien LE COUVIOUR--TUFFET
//

#include "DataBaseEntity.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    Entity::~Entity(void) {}

    bool	Entity::hasComponent(std::string const & name) const	{ return _namesIdxMap.find(name) != _namesIdxMap.end(); }

    Component &
    Entity::getComponent(std::string const & name)
    {
      if (_namesIdxMap.find(name) == _namesIdxMap.end())
	throw IdentifierNotFound(name);
      return _components[_namesIdxMap.at(name)];
    }

    Component const &
    Entity::getComponent(std::string const & name) const
    {
      if (_namesIdxMap.find(name) == _namesIdxMap.end())
	throw IdentifierNotFound(name);
      return _components[_namesIdxMap.at(name)];
    }

    Component &		Entity::operator[](std::string const & name)		{ return this->getComponent(name); }
    Component const &	Entity::operator[](std::string const & name) const	{ return this->getComponent(name); }

    Component &
    Entity::setComponent(std::string const & name, Component const & component)
    {
      if (_namesIdxMap.find(name) == _namesIdxMap.end())
	{
	  _namesIdxMap.emplace(name, _components.size());
	  _components.emplace(_components.end(), component);
	}
      else
	_components[_namesIdxMap[name]] = component;
      return this->getComponent(name);
    }

    Component
    Entity::delComponent(std::string const & name)
    {
      if (_namesIdxMap.find(name) == _namesIdxMap.end())
	throw IdentifierNotFound(name);
      {
	Component const		component = this->getComponent(name);
	unsigned const		idx = _namesIdxMap.at(name);

	_components.erase(_components.begin() + idx);
	_namesIdxMap.erase(name);
	for (auto & pair : _namesIdxMap)
	  if (pair.second > idx)
	    --pair.second;
	return component;
      }
    }

    std::ostream &
    operator<<(std::ostream & os, Entity const & e)
    {
      auto	it = e._namesIdxMap.begin();

      os << "[with ";
      while (it != e._namesIdxMap.end())
	{
	  os << it->first << ": " << e._components[it->second];
	  if (++it != e._namesIdxMap.end())
	    os << ", ";
	  else
	    os << ']';
	}
      return os;
    }
  }
}
