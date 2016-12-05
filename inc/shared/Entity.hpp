//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec  5 19:42:01 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"

namespace	entity_component_system
{
  namespace	entity
  {
    class	Entity
    {
    public:
      template<typename... ComponentsNames>
      Entity(std::initializer_list<component::Component> && components, ComponentsNames&&... names) : Entity("unknownEntity", components, 0, names...) {}

      template<typename... ComponentsNames>
      Entity(std::string const & name, std::initializer_list<component::Component> && components, ComponentsNames&&... names) : Entity(name, components, 0, names...) {}

    private:
      template<typename... ComponentsNames>
      Entity(std::string const & name, std::initializer_list<component::Component> const & components, unsigned i, ComponentsNames&&... names)
	: _name(name), _components(components), _namesIdxMap({{names, i++}...}) {}

    public:
      Entity(Entity const &) = default;
      Entity(Entity &&) = default;
      ~Entity(void) {}

      bool	hasComponent(std::string const & name)	{ return _namesIdxMap.find(name) != _namesIdxMap.end(); }

      component::Component &		getComponent(std::string const & name)		{ return _components[_namesIdxMap.at(name)]; }
      component::Component const &	getComponent(std::string const & name) const	{ return _components[_namesIdxMap.at(name)]; }

      component::Component &		operator[](std::string const & name)		{ return _components[_namesIdxMap.at(name)]; }
      component::Component const &	operator[](std::string const & name) const	{ return _components[_namesIdxMap.at(name)]; }

      void				setComponent(std::string const & name, component::Component const & component)
      {
	if (_namesIdxMap.find(name) == _namesIdxMap.end())
	  {
	    _namesIdxMap.emplace(name, _components.size());
	    _components.emplace(_components.end(), component);
	  }
	else
	  _components[_namesIdxMap[name]] = component;
      }

      component::Component		delComponent(std::string const & name)
      {
	component::Component const	component = (*this)[name];
	unsigned const			idx = _namesIdxMap.at(name);

	_components.erase(_components.begin() + idx);
	_namesIdxMap.erase(name);
	for (auto & pair : _namesIdxMap)
	  if (pair.second > idx)
	    --pair.second;
	return component;
      }

      friend std::ostream &	operator<<(std::ostream & os, Entity const & e)
      {
	os << e._name << std::endl;
	for (auto & pair : e._namesIdxMap)
	  {
	    os << '\t' << pair.first << std::endl;
	    os << e._components[pair.second];
	  }
	os << "-------------------" << std::flush;
	return os;
      }

    private:
      std::string const				_name;
      std::vector<component::Component>		_components;
      std::map<std::string, unsigned>		_namesIdxMap;
    };
  }
}
