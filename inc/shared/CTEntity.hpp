//
// CTEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 10 04:57:13 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 21:38:41 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    class	Entity;
  }

  namespace	entity
  {
    template<typename, char const *...>
    class	CTEntity;

    template<typename... ComponentsTypes, char const *... names>
    class	CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>
    {
    public:
      CTEntity(void) = default;
      CTEntity(ComponentsTypes const &... components) : _components(components...) {}
      CTEntity(ComponentsTypes&&... components) : _components(std::forward<ComponentsTypes>(components)...) {}
      CTEntity(database::Entity const & databaseEntity) : _components(_initComponents(databaseEntity, std::true_type())) {}
      CTEntity(database::Entity && databaseEntity) : _components(_initComponents(std::forward<database::Entity>(databaseEntity), std::true_type())) {}
      CTEntity(CTEntity const &) = default;
      CTEntity(CTEntity &&) = default;
      ~CTEntity(void) = default;

      CTEntity &
      operator=(database::Entity const & databaseEntity)
      {
	_components = _initComponents(databaseEntity, std::true_type());
	return *this;
      }

      CTEntity &
      operator=(database::Entity && databaseEntity)
      {
	_components = _initComponents(std::forward<database::Entity>(databaseEntity), std::true_type());
	return *this;
      }

      CTEntity &	operator=(CTEntity const &) = default;
      CTEntity &	operator=(CTEntity &&) = default;

      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type &
      getComponent(void)
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type const &
      getComponent(void) const
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type const &
      getComponent(unsigned) const
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type const & component)
      {
	std::get<ct::getIdx<name, names...>()>(_components) = component;
      }

      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type && component)
      {
	std::get<ct::getIdx<name, names...>()>(_components) = std::forward<typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type>(component);
      }

      friend std::ostream &	operator<<(std::ostream & os, CTEntity const & e)
      {
	os << "[with ";
	return e._print<names...>(os) << ']' << std::flush;
      }

    private:
      std::tuple<ComponentsTypes...>	_components;

    private:
      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity const & databaseEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity const &, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
      }

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity && databaseEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity &&, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
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

#include "DataBaseEntity.hpp"

template<typename... ComponentsTypes, char const *... names> template<typename... Components>
std::tuple<ComponentsTypes...>
entity_component_system::entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(database::Entity const & databaseEntity, std::true_type, Components&&... components)
{
  return _initComponents(databaseEntity,
			 std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			 std::forward<Components>(components)...,
			 databaseEntity[std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))]);
}

template<typename... ComponentsTypes, char const *... names> template<typename... Components>
std::tuple<ComponentsTypes...>
entity_component_system::entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(database::Entity && databaseEntity, std::true_type, Components&&... components)
{
  return _initComponents(std::forward<database::Entity>(databaseEntity),
			 std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			 std::forward<Components>(components)...,
			 std::move(databaseEntity[std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))]));
}
