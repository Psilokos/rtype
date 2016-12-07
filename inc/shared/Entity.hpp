//
// Entity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec  2 14:09:55 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec  7 14:17:13 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"
#include "IdentifierNotFound.hpp"

namespace	entity_component_system
{
  namespace	entity
  {
    //! \brief Generic class for all entities
    class	Entity
    {
    public:
      //! \brief Constructor
      //! \param [in] components an initializer list of the components to store
      //! \param [in] names the names of the components to store
      template<typename... ComponentsNames>
      Entity(std::initializer_list<component::Component> && components, ComponentsNames&&... names) : Entity("unknownEntity", components, 0, names...) {}

      //! \brief Constructor
      //! \param [in] name the name of the entity
      //! \param [in] components an initializer list of the components to store
      //! \param [in] names the names of the components to store
      template<typename... ComponentsNames>
      Entity(std::string const & name, std::initializer_list<component::Component> && components, ComponentsNames&&... names) : Entity(name, components, 0, names...) {}

    private:
      template<typename... ComponentsNames>
      Entity(std::string const & name, std::initializer_list<component::Component> const & components, unsigned i, ComponentsNames&&... names)
	: _name(name), _components(components), _namesIdxMap({{names, i++}...}) {}

    public:
      //! \brief Default copy constructor
      Entity(Entity const &) = default;
      //! \brief Default move constructor
      Entity(Entity &&) = default;
      //! \brief Destructor
      ~Entity(void);

      //! \brief Check if a component exists
      //! \param [in] name the name of the component to check
      //! \return true if the component exists, false otherwise
      bool	hasComponent(std::string const & name) const;

      //! \brief Get a component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      component::Component &		getComponent(std::string const & name);

      //! \brief Get a constant component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the constant requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      component::Component const &	getComponent(std::string const & name) const;

      //! \brief Get a component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      component::Component &		operator[](std::string const & name);

      //! \brief Get a constant component
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the constant requested component if found, raises an ecs::IdentifierNotFound exception otherwise
      component::Component const &	operator[](std::string const & name) const;

      //! \brief Set a component
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      component::Component &		setComponent(std::string const & name, component::Component const & component);

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \return a shallow copy of the removed component
      component::Component		delComponent(std::string const & name);

      //! \brief Insert an entity into an output stream
      //! \param [out] os the output stream in which the given entity will be inserted
      //! \param [in] e the entity to insert in the stream
      //! \return the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Entity const & e);

    private:
      std::string const				_name;
      std::vector<component::Component>		_components;
      std::map<std::string, unsigned>		_namesIdxMap;
    };
  }
}
