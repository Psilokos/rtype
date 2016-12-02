//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Fri Dec  2 19:28:46 2016 Victorien LE COUVIOUR--TUFFET
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
      Entity(std::initializer_list<component::Component> && components, ComponentsNames&&... names) : Entity(components, 0, names...) {}

    private:
      template<typename... ComponentsNames>
      Entity(std::initializer_list<component::Component> const & components, unsigned i, ComponentsNames&&... names) : _components(components), _namesIdxMap({{names, i++}...}) {}

    public:
      Entity(Entity const &) = default;
      Entity(Entity &&) = default;
      ~Entity(void) {}

      void				addComponent(std::string const & name, component::Component const & component)
      {
	_namesIdxMap.emplace(name, _components.size());
	_components.emplace(_components.end(), component);
      }

      component::Component		removeComponent(std::string const & name)
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

      component::Component &		component(std::string const & name)		{ return _components[_namesIdxMap.at(name)]; }
      component::Component const &	component(std::string const & name) const	{ return _components[_namesIdxMap.at(name)]; }

      component::Component &		operator[](std::string const & name)		{ return _components[_namesIdxMap.at(name)]; }
      component::Component const &	operator[](std::string const & name) const	{ return _components[_namesIdxMap.at(name)]; }

    private:
      std::vector<component::Component>		_components;
      std::map<std::string, unsigned>		_namesIdxMap;
    };
  }
}
