//
// DataBaseEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec 13 15:09:22 2016 Victorien LE COUVIOUR--TUFFET
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

    class	RTEntity;
  }

  namespace	database
  {
    //! \brief Generic class for all entities
    class	Entity
    {
    public:
      //! \brief Default constructor
      Entity(void) = default;

      //! \brief Constructor
      //! \param [in] components an initializer list of the components to store
      //! \param [in] names the names of the components to store
      Entity(std::initializer_list<std::pair<std::size_t const, Component>> && components);

      //! \brief Default copy constructor
      Entity(Entity const &) = default;

      //! \brief Default move constructor
      Entity(Entity &&) = default;

      //! \brief Destructor
      ~Entity(void) = default;

      //! \brief entity::CTEntity assignement by copy operator
      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e)
      {
	_Assign<names...>	assign(e, _components);

	return *this;
      }

      //! \brief entity::CTEntity assignement by move operator
      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e)
      {
	_Assign<names...>	assign(std::move(e), _components);

	return *this;
      }

      //! \brief entity::RTEntity assignement by copy operator
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity &
      assign(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names)
      {
	_setComponents(e, std::move(types), std::string(std::forward<ComponentsNames>(names))...);
	return *this;
      }

      //! \brief entity::RTEntity assignement by move operator
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity &
      assign(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names)
      {
	_setComponents(std::move(e), std::move(types), std::string(std::forward<ComponentsNames>(names))...);
	return *this;
      }

      //! \brief Default assignement by copy operator
      Entity &	operator=(Entity const &) = default;

      //! \brief Default assignement by move operator
      Entity &	operator=(Entity &&) = default;

      //! \brief Checks if a component exists
      //! \param [in] name the name of the component to check
      //! \return true if the component exists, false otherwise
      bool	hasComponent(std::string const & name) const;

      //! \brief Adds a Component by copy
      //! \param [in] component the Component to add
      void	addComponent(std::string const & name, Component const & component);

      //! \brief Adds a Component by move
      //! \param [in] component the Component to add
      void	addComponent(std::string const & name, Component && component);

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the requested Component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &	getComponent(std::string const & name);

      //! \brief Gets a constant Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the constant requested Component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component const &	getComponent(std::string const & name) const;

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the requested Component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &	operator[](std::string const & name);

      //! \brief Gets a constant Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the constant requested Component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component const &	operator[](std::string const & name) const;

      //! \brief Sets a Component by copy
      //! \param [in] name the name of the Component to set
      //! \param [in] component the Component to set
      //! \return a reference to the set Component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &	setComponent(std::string const & name, Component const & component);

      //! \brief Sets a Component by move
      //! \param [in] name the name of the Component to set
      //! \param [in] component the Component to set
      //! \return a reference to the set component if found, raises an ecs::IdentifierNotFound exception otherwise
      Component &	setComponent(std::string const & name, Component && component);

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \return a copy of the removed component
      Component		delComponent(std::string const & name);

      //! \brief Inserts an Entity into an output stream
      //! \param [out] os the output stream in which the given entity will be inserted
      //! \param [in] e the Entity to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Entity const & e);

    private:
      std::map<std::size_t, Component>	_components;

    private:
      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names, typename std::enable_if<idx < sizeof...(ComponentsNames), void *>::type = nullptr);

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> &&, ComponentsNames&&... names, typename std::enable_if<idx == sizeof...(ComponentsNames), void *>::type = nullptr) {}

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names, typename std::enable_if<idx < sizeof...(ComponentsNames), void *>::type = nullptr);

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> &&, ComponentsNames&&... names, typename std::enable_if<idx == sizeof...(ComponentsNames), void *>::type = nullptr) {}

    private:
      template<char const *... names>
      class	_Assign
      {
      private:
	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::size_t, Component> &, typename std::enable_if<idx < sizeof...(names), void *>::type = 0);

	template<unsigned idx, typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::size_t, Component> &, typename std::enable_if<idx == sizeof...(names), void *>::type = 0) {}

	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::size_t, Component> &, typename std::enable_if<idx < sizeof...(names), void *>::type = 0);

	template<unsigned idx, typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::size_t, Component> &, typename std::enable_if<idx == sizeof...(names), void *>::type = 0) {}

      public:
	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e, std::map<std::size_t, Component> & components)
	{
	  _setComponents<0, names...>(e, components);
	}

	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e, std::map<std::size_t, Component> & components)
	{
	  _setComponents<0, names...>(std::forward<entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>(e), components);
	}
      };
    };
  }
}

#include "CTEntity.hpp"
#include "RTEntity.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
    void
    Entity::_setComponents(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names, typename std::enable_if<idx < sizeof...(ComponentsNames), void *>::type)
    {
      if (_components.find(std::get<idx>(std::tuple<decltype(names)...>(names...))) == _components.end()) // inline c++17 equivalent std::map::insert_or_assign
	_components.emplace(std::get<idx>(std::tuple<decltype(names)...>(names...)),
			    e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(std::tuple<decltype(names)...>(names...))));
      else
	_components.at(std::get<idx>(std::tuple<decltype(names)...>(names...)) =
		       e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(std::tuple<decltype(names)...>(names...))));
      return _setComponents<idx + 1>(e, std::move(types), names...);
    }

    template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
    void
    Entity::_setComponents(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names, typename std::enable_if<idx < sizeof...(ComponentsNames), void *>::type)
    {
      if (_components.find(std::get<idx>(std::tuple<decltype(names)...>(names...))) == _components.end()) // inline c++17 equivalent std::map::insert_or_assign
	_components.emplace(std::get<idx>(std::tuple<decltype(names)...>(names...)),
			    std::move(e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(std::tuple<decltype(names)...>(names...)))));
      else
	_components.at(std::get<idx>(std::tuple<decltype(names)...>(names...)) =
		       std::move(e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(std::tuple<decltype(names)...>(names...)))));
      return _setComponents<idx + 1>(std::move(e), std::move(types), names...);
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... ComponentsTypes>
    void
    Entity::_Assign<names...>::_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e,
					      std::map<std::size_t, Component> & components, typename std::enable_if<idx < sizeof...(names), void *>::type)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (components.find(hashedKey) == components.end())
	throw IdentifierNotFound(name);
      components.at(hashedKey) = e.template getComponent<name>();
      _setComponents<idx + 1, _names...>(e, components);
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... ComponentsTypes>
    void
    Entity::_Assign<names...>::_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e,
					      std::map<std::size_t, Component> & components, typename std::enable_if<idx < sizeof...(names), void *>::type)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (components.find(hashedKey) == components.end())
	throw IdentifierNotFound(name);
      components.at(hashedKey) = std::move(e.template getComponent<name>());
      _setComponents<idx + 1, _names...>(std::forward<entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>(e), components);
    }
  }
}
