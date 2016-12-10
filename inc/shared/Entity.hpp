//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 10 04:57:13 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 10 17:45:33 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"
#include "DataBaseEntity.hpp"

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
      Entity(database::Entity const & databaseEntity) : _components(_initComponents(databaseEntity, std::true_type())) {}
      Entity(Entity const &) = default;
      Entity(Entity &&) = default;
      ~Entity(void) = default;

      Entity &
      operator=(database::Entity const & databaseEntity)
      {
	_components = _initComponents(databaseEntity, std::true_type());
	return *this;
      }

      Entity &	operator=(Entity const &) = default;
      Entity &	operator=(Entity &&) = default;

      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentTypes...>>::type &
      getComponent(void)
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentTypes...>>::type const &
      getComponent(void) const
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentTypes...>>::type const & component)
      {
	std::get<ct::getIdx<name, names...>()>(_components) = component;
      }

      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentTypes...>>::type && component)
      {
	std::get<ct::getIdx<name, names...>()>(_components) = std::forward<typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentTypes...>>::type>(component);
      }

      friend std::ostream &	operator<<(std::ostream & os, Entity const & e)
      {
	os << "[with ";
	return e._print<names...>(os) << ']' << std::flush;
      }

    private:
      std::tuple<ComponentTypes...>	_components;

    private:
      template<typename... Components>
      std::tuple<ComponentTypes...>
      _initComponents(database::Entity const & databaseEntity, std::true_type, Components&&... components)
      {
	return _initComponents(databaseEntity,
			       std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentTypes)>(),
			       std::forward<Components>(components)...,
			       databaseEntity[std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))]);
      }

      template<typename... Components>
      std::tuple<ComponentTypes...>
      _initComponents(database::Entity const &, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentTypes...>(std::forward<ComponentTypes>(components)...);
      }

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
