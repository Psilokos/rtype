//
// DataBaseEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 15 22:56:49 2016 Victorien LE COUVIOUR--TUFFET
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
    //! \brief Class representing an entity in the database
    class	Entity
    {
    public:
      //! \brief Default constructor
      Entity(void) = default;

      //! \brief Constructor initializing components from an initializer list
      //! \param [in] components an initializer list of pair containing the hash of the component name and the Component. The hash is obtained as follow: \code std::hash<std::string>{}("name"); \endcode
      Entity(std::initializer_list<std::pair<std::size_t const, Component>> && components);

      //! \brief Constructor initializing components by copy from an entity::CTEntity
      //! \param [in] e the source entity
      template<typename... ComponentsTypes, char const *... names>
      Entity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e);

      //! \brief Constructor initializing components by move from an entity::CTEntity
      //! \param [in] e the source entity
      template<typename... ComponentsTypes, char const *... names>
      Entity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e);

      //! \brief Constructor initializing components by copy from an entity::RTEntity
      //! \param [in] e the source entity
      //! \param [in] types a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component is not found in 'e'
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names);

      //! \brief Constructor initializing components by move from an entity::RTEntity
      //! \param [in] e the source entity
      //! \param [in] types a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component is not found in 'e'
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names);

      //! \brief Default copy constructor
      Entity(Entity const &) = default;

      //! \brief Default move constructor
      Entity(Entity &&) = default;

      //! \brief Destructor
      ~Entity(void) = default;

      //! \brief Assignement operator, setting the components by copy from a CTEntity
      //! \param [in] e the source entity
      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e)
      {
	_Assign<names...>	assign(e, _components);

	return *this;
      }

      //! \brief Assignement operator, setting the components by copy from a CTEntity
      //! \param [in] e the source entity
      template<typename... ComponentsTypes, char const *... names>
      Entity &
      operator=(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e)
      {
	_Assign<names...>	assign(std::move(e), _components);

	return *this;
      }

      //! \brief Sets the components by copy from an entity::RTEntity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] rtEntity the source entity
      //! \param [in] types a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in rtEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity &
      assign(entity::RTEntity const & rtEntity, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names)
      {
	_setComponents<0>(rtEntity, std::move(types), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
	return *this;
      }

      //! \brief Sets the components by move from an entity::RTEntity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] rtEntity the source entity
      //! \param [in] types a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in rtEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      Entity &
      assign(entity::RTEntity && rtEntity, ct::TypesWrapper<ComponentsTypes...> && types, ComponentsNames&&... names)
      {
	_setComponents<0>(std::move(rtEntity), std::move(types), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
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

      //! \brief Adds a component by copy
      //! \param [in] name the name of the Component to add
      //! \param [in] component the Component to add
      //! \throw IdentifierFound if a component with the same name already exists
      void	addComponent(std::string const & name, Component const & component);

      //! \brief Adds a component by move
      //! \param [in] name the name of the Component to add
      //! \param [in] component the Component to add
      //! \throw IdentifierFound if a component with the same name already exists
      void	addComponent(std::string const & name, Component && component);

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the requested Component
      //! \throw IdentifierNotFound if the component does not exist
      Component &	getComponent(std::string const & name);

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the constant requested Component
      //! \throw IdentifierNotFound if the component does not exist
      Component const &	getComponent(std::string const & name) const;

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the requested Component
      //! \throw IdentifierNotFound if the component does not exist
      Component &	operator[](std::string const & name);

      //! \brief Gets a Component
      //! \param [in] name the name of the Component to get
      //! \return an lvalue reference to the constant requested Component
      //! \throw IdentifierNotFound if the component does not exist
      Component const &	operator[](std::string const & name) const;

      //! \brief Sets a Component by copy
      //! \param [in] name the name of the Component to set
      //! \param [in] component the Component to set
      //! \throw IdentifierNotFound if the Component does not exist
      void	setComponent(std::string const & name, Component const & component);

      //! \brief Sets a Component by move
      //! \param [in] name the name of the Component to set
      //! \param [in] component the Component to set
      //! \throw IdentifierNotFound if the Component does not exist
      void	setComponent(std::string const & name, Component && component);

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \return a copy of the removed component
      //! \throw IdentifierNotFound if the Component does not exist
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
      _setComponents(entity::RTEntity const &, ct::TypesWrapper<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> &&, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity const &, ct::TypesWrapper<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> &&, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr) {}

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity &&, ct::TypesWrapper<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> &&, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
      void
      _setComponents(entity::RTEntity &&, ct::TypesWrapper<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> &&, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr) {}

    private:
      template<char const *... names>
      class	_Assign
      {
      private:
	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::size_t, Component> &, typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

	template<unsigned idx, typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, std::map<std::size_t, Component> &, typename std::enable_if<idx == sizeof...(names)>::type * = nullptr) {}

	template<unsigned idx, char const *, char const *..., typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::size_t, Component> &, typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

	template<unsigned idx, typename... ComponentsTypes>
	void	_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, std::map<std::size_t, Component> &, typename std::enable_if<idx == sizeof...(names)>::type * = nullptr) {}

      public:
	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e, std::map<std::size_t, Component> & components)
	{
	  _setComponents<0, names...>(e, components);
	}

	template<typename... ComponentsTypes>
	_Assign(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e, std::map<std::size_t, Component> & components)
	{
	  _setComponents<0, names...>(std::move(e), components);
	}
      };
    };
  }
}

#include "RTEntity.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<typename... ComponentsTypes, char const *... names>
    Entity::Entity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e) : _components({{std::hash<std::string>{}(names), e.template getComponent<names>()}...}) {}

    template<typename... ComponentsTypes, char const *... names>
    Entity::Entity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && e) : _components({{std::hash<std::string>{}(names), std::move(e.template getComponent<names>())}...}) {}

    template<typename... ComponentsTypes, typename... ComponentsNames>
    Entity::Entity(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> &&, ComponentsNames&&... names)
      : _components({{std::hash<std::string>{}(names), e.getComponent<ComponentsTypes>(std::forward<ComponentsNames>(names))}...}) {}

    template<typename... ComponentsTypes, typename... ComponentsNames>
    Entity::Entity(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> &&, ComponentsNames&&... names)
      : _components({{std::hash<std::string>{}(names), std::move(e.getComponent<ComponentsTypes>(std::forward<ComponentsNames>(names)))}...}) {}

    template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
    void
    Entity::_setComponents(entity::RTEntity const & e, ct::TypesWrapper<ComponentsTypes...> && types, ct::Wrapper<ComponentsNames...> && names, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(std::get<idx>(names.values));

      if (_components.find(hashedKey) == _components.end()) // inline c++17 equivalent => std::map::insert_or_assign
	_components.emplace(hashedKey, e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(names.values)));
      else
	_components.at(hashedKey) = e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(names.values));
      return _setComponents<idx + 1>(e, std::move(types), std::move(names));
    }

    template<unsigned idx, typename... ComponentsTypes, typename... ComponentsNames>
    void
    Entity::_setComponents(entity::RTEntity && e, ct::TypesWrapper<ComponentsTypes...> && types, ct::Wrapper<ComponentsNames...> && names, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(std::get<idx>(names.values));

      if (_components.find(hashedKey) == _components.end()) // inline c++17 equivalent => std::map::insert_or_assign
	_components.emplace(hashedKey, std::move(e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(names.values))));
      else
	_components.at(hashedKey) = std::move(e.getComponent<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(names.values)));
      return _setComponents<idx + 1>(std::move(e), std::move(types), std::move(names));
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... ComponentsTypes>
    void
    Entity::_Assign<names...>::_setComponents(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & e,
					      std::map<std::size_t, Component> & components, typename std::enable_if<idx < sizeof...(names)>::type *)
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
					      std::map<std::size_t, Component> & components, typename std::enable_if<idx < sizeof...(names)>::type *)
    {
      std::size_t const	hashedKey = std::hash<std::string>{}(name);

      if (components.find(hashedKey) == components.end())
	throw IdentifierNotFound(name);
      components.at(hashedKey) = std::move(e.template getComponent<name>());
      _setComponents<idx + 1, _names...>(std::move(e), components);
    }
  }
}
