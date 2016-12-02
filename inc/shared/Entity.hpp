//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Fri Dec  2 17:21:56 2016 Victorien LE COUVIOUR--TUFFET
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
      Entity(std::initializer_list<component::Component> & components, unsigned i, ComponentsNames&&... names) : _components(components), _namesIdxMap({{names, i++}...}) {}

    public:
      Entity(Entity const &) = default;
      Entity(Entity &&) = default;
      ~Entity(void) {}

      component::Component const &	component(std::string const & name) const { return _components[_namesIdxMap.at(name)]; }

    private:
      std::vector<component::Component>		_components;
      std::map<std::string, unsigned>		_namesIdxMap;
    };
  }
}
