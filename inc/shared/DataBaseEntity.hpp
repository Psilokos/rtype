//
// DataBaseEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 21:39:40 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "DataBaseComponent.hpp"
#include "IdentifierNotFound.hpp"

namespace	entity_component_system
{
  namespace	entity
  {
    template<typename, char const *...>
    class	CTEntity;

    template<typename... ComponentsTypes, char const *... names>
    class	CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>;
  }

  namespace	database
  {
    //! \brief Generic class for all entities
    class	Entity
    {
    public:
      //! \brief Constructor
      //! \param [in] components an initializer list of the components to store
      //! \param [in] names the names of the components to store
      template<typename... ComponentsNames>
      Entity(std::initializer_list<Component> && components, ComponentsNames&&... names) : Entity(components, 0, names...) {}

    private:
      template<typename... ComponentsNames>
      Entity(std::initializer_list<Component> const & components, unsigned i, ComponentsNames&&... names) : _components(components), _namesIdxMap({{names, i++}...}) {}

    public:
      //! \brief Default copy constructor
      Entity(Entity const &) = default;
      //! \brief Default move constructor
      Entity(Entity &&) = default;
      //! \brief Destructor
      ~Entity(void);

      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e)
      {
	_Assign<names...>	assign(e, _namesIdxMap, _components);

	return *this;
      }

      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e)
      {
	_Assign<names...>	assign(std::forward<entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>(e), _namesIdxMap, _components);

	return *this;
      }

      //! \brief Default copy assignement operator
      Entity &	operator=(Entity const &) = default;
      //! \brief Default move assignement operator
      Entity &	operator=(Entity &&) = default;

      //! \brief Check if a component exists
      //! \param [in] name the name of the component to check
      //! \return true if the component exists, false otherwise
      bool	hasComponent(std::string const & name) const;

      //! \brief Get a component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &		getComponent(std::string const & name);

      //! \brief Get a constant component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the constant requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component const &		getComponent(std::string const & name) const;

      //! \brief Get a component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &		operator[](std::string const & name);

      //! \brief Get a constant component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the constant requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component const &		operator[](std::string const & name) const;

      //! \brief Set a component
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      //! \return a reference to the set component
      Component &		setComponent(std::string const & name, Component const & component);

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \return a shallow copy of the removed component
      Component		delComponent(std::string const & name);

      //! \brief Insert an entity into an output stream
      //! \param [out] os the output stream in which the given entity will be inserted
      //! \param [in] e the entity to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Entity const & e);

    private:
      std::vector<Component>		_components;
      std::map<std::string, unsigned>	_namesIdxMap;

    private:
      template<char const *... names>
      class	_Assign
      {
      private:
	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void
	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::string, unsigned> const &,
		       std::vector<Component> &, typename std::enable_if<idx < sizeof...(names), void *>::type = 0);

	template<unsigned idx, typename... ComponentsTypes>
	void
	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::string, unsigned> const &,
		       std::vector<Component> &, typename std::enable_if<idx == sizeof...(names), void *>::type = 0)
	{}

	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void
	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::string, unsigned> const &,
		       std::vector<Component> &, typename std::enable_if<idx < sizeof...(names), void *>::type = 0);

	template<unsigned idx, typename... ComponentsTypes>
	void
	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::string, unsigned> const &,
		       std::vector<Component> &, typename std::enable_if<idx == sizeof...(names), void *>::type = 0)
	{}

      public:
	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e, std::map<std::string, unsigned> const & namesIdxMap, std::vector<Component> & components)
	{
	  _setComponents<0, names...>(e, namesIdxMap, components);
	}

	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e, std::map<std::string, unsigned> const & namesIdxMap, std::vector<Component> & components)
	{
	  _setComponents<0, names...>(std::forward<entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>(e), namesIdxMap, components);
	}
      };
    };
  }
}

#include "Entity.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... ComponentsTypes>
    void
    Entity::_Assign<names...>::_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e, std::map<std::string, unsigned> const & namesIdxMap,
					      std::vector<Component> & components, typename std::enable_if<idx < sizeof...(names), void *>::type)
    {
      if (namesIdxMap.find(name) == namesIdxMap.end())
	throw IdentifierNotFound(name);
      components[namesIdxMap.at(name)] = e.template getComponent<name>();
      _setComponents<idx + 1, _names...>(e, namesIdxMap, components);
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... ComponentsTypes>
    void
    Entity::_Assign<names...>::_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e, std::map<std::string, unsigned> const & namesIdxMap,
					      std::vector<Component> & components, typename std::enable_if<idx < sizeof...(names), void *>::type)
    {
      if (namesIdxMap.find(name) == namesIdxMap.end())
	throw IdentifierNotFound(name);
      components[namesIdxMap.at(name)] = std::move(e.template getComponent<name>());
      _setComponents<idx + 1, _names...>(std::forward<entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>(e), namesIdxMap, components);
    }
  }
}
