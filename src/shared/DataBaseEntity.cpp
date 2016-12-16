//
// Entity.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 13:36:34 2016 Victorien LE COUVIOUR--TUFFET
// Last update Fri Dec 16 00:34:40 2016 Victorien LE COUVIOUR--TUFFET
//

#include "DataBaseEntity.hpp"
#include "IdentifierFound.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    Entity::Entity(ID<ecs::Entity> const & id) : _id(id) {}

    Entity::Entity(ID<ecs::Entity> const & id, std::initializer_list<std::pair<std::size_t const, Component>> && components) : _id(id), _components(components) {}

    ID<ecs::Entity>	Entity::getID(void) const { return _id; }

    void	Entity::setID(ID<ecs::Entity> const & id) { _id = id; }

    bool	Entity::hasComponent(std::string const & name) const { return _components.find(std::hash<std::string>{}(name)) != _components.end(); }

    void
    Entity::addComponent(std::string const & name, Component const & component)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) != _components.end())
	throw IdentifierFound(name);
      _components.emplace(hashedKey, component);
    }

    void
    Entity::addComponent(std::string const & name, Component && component)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) != _components.end())
	throw IdentifierFound(name);
      _components.emplace(hashedKey, component);
    }

    Component &
    Entity::getComponent(std::string const & name)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) == _components.end())
	throw IdentifierNotFound(name);
      return _components.at(hashedKey);
    }

    Component const &
    Entity::getComponent(std::string const & name) const
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) == _components.end())
	throw IdentifierNotFound(name);
      return _components.at(hashedKey);
    }

    Component &		Entity::operator[](std::string const & name)		{ return this->getComponent(name); }
    Component const &	Entity::operator[](std::string const & name) const	{ return this->getComponent(name); }

    void
    Entity::setComponent(std::string const & name, Component const & component)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) == _components.end())
	throw IdentifierNotFound(name);
      if (&component != &_components.at(hashedKey))
	_components.at(hashedKey) = component;
    }

    void
    Entity::setComponent(std::string const & name, Component && component)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) == _components.end())
	throw IdentifierNotFound(name);
      if (&component != &_components.at(hashedKey))
	_components.at(hashedKey) = component;
    }

    Component
    Entity::delComponent(std::string const & name)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (_components.find(hashedKey) == _components.end())
	throw IdentifierNotFound(name);
      {
	Component const	component = _components.at(hashedKey);

	_components.erase(hashedKey);
	return component;
      }
    }

    std::ostream &
    operator<<(std::ostream & os, Entity const & e)
    {
      auto	it = e._components.begin();

      os << "[with ";
      while (it != e._components.end())
	{
	  os << it->first << ": " << it->second;
	  if (++it != e._components.end())
	    os << ", ";
	  else
	    os << ']';
	}
      return os;
    }
  }
}
