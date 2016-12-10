//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 10 04:57:13 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 10 07:13:24 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"

namespace	entity_component_system
{
  namespace	entity
  {
    template<typename, char const *...>
    class	Entity;

    template<typename... ComponentTypes, char const *... names>
    class	Entity<ct::TypesWrapper<ComponentTypes...>, names...>
    {
    public:
      Entity(void) = default;
      Entity(ComponentTypes const &... components) : _components(components...) {}
      Entity(ComponentTypes&&... components) : _components(std::forward<ComponentTypes>(components)...) {}
      Entity(Entity const &) = default;
      Entity(Entity &&) = default;
      ~Entity(void) = default;

      friend std::ostream &	operator<<(std::ostream & os, Entity const & e)
      {
	os << "[with ";
	return e._print<names...>(os) << ']' << std::flush;
      }

    private:
      std::tuple<ComponentTypes...>	_components;

    private:
      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<sizeof...(_names), void *>::type = 0) const
      {
	os << name << ": " << std::get<sizeof...(names) - sizeof...(_names) - 1>(_components) << ", ";
	return _print<_names...>(os);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<!sizeof...(_names), void *>::type = 0) const
      {
	return os << name << ": " << std::get<sizeof...(names) - 1>(_components);
      }
    };
  }
}
