//
// Component.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 17:12:15 2016 Victorien LE COUVIOUR--TUFFET
// Last update Fri Dec 16 00:58:55 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <ostream>
#include <string>
#include <tuple>
#include "CompileTime.hpp"
#include "ID.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    class	Component;
  }

  namespace	component
  {
    //! \brief Compile time component class (see its specialization below)
    template<typename, char const *...>
    class	Component;

    //! \brief Compile time component class
    //!
    //! this class is designed to represent a component outside of the database
    //! \tparam Types the types of the component's attributes
    //! \tparam names the names of the component's attributes, in the same order as the types are. Must be declared as follow (in the global scope): \code constexpr char attrName[] = "attrName"; \endcode
    template<typename... Types, char const *... names>
    class	Component<ct::TypesWrapper<Types...>, names...>
    {
    public:
      //! \brief Default constructor
      Component(void) = default;

      //! \brief Constructor initializing the id
      //! \param [in] id the ID of the component in database
      Component(ID<ecs::Component> const & id) : _id(id) {}

      //! \brief Constructor initializing the attributes by copy
      //! \param [in] id the ID of the component in database
      //! \param [in] values values to initialize attributes
      Component(ID<ecs::Component> const & id, Types const &... values) : _id(id), _values(values...) {}

      //! \brief Constructor initializing the attributes by move
      //! \param [in] id the ID of the component in database
      //! \param [in] values values to initialize attributes
      Component(ID<ecs::Component> const & id, Types&&... values) : _id(id), _values(std::forward<Types>(values)...) {}

      //! \brief Constructor initializing the attribute by copy from a database::Component
      //! \param [in] databaseComponent the source component
      //! \throw IdentifierNotFound if an attribute is not found in the databaseComponent
      Component(database::Component const & databaseComponent);

      //! \brief Constructor initializing the attribute by move from a database::Component
      //! \param [in] databaseComponent the source component
      //! \throw IdentifierNotFound if an attribute is not found in the databaseComponent
      Component(database::Component && databaseComponent);

      //! \brief Default copy constructor
      Component(Component const &) = default;

      //! \brief Default move constructor
      Component(Component &&) = default;

      //! \brief Default destructor
      ~Component(void) = default;

      //! \brief Assignement operator, setting the attributes by copy from a database::Component
      //! \param [in] databaseComponent the source component
      //! \throw IdentifierNotFound if an attribute is not found in the databaseComponent
      Component &	operator=(database::Component const & databaseComponent);

      //! \brief Assignement operator, setting the attributes by move from a database::Component
      //! \param [in] databaseComponent the source component
      //! \throw IdentifierNotFound if an attribute is not found in the databaseComponent
      Component &	operator=(database::Component && databaseComponent);

      //! \brief Default copy assignement operator
      Component &	operator=(Component const &) = default;

      //! \brief Default move assignement operator
      Component &	operator=(Component &&) = default;

      //! \brief Gets the component ID
      //! \return a copy of the component's ID
      ID<ecs::Component>	getID(void) const { return _id; }

      //! \brief Sets the component ID
      //! \param [in] id the new ID
      void	setID(ID<ecs::Component> const & id) { _id = id; }

      //! \brief Gets an attribute
      //! \tparam name the name of the requested attribute, must be declared as follow (in the global scope): \code constexpr char attrName[] = "attrName"; \endcode
      //! \return an lvalue reference to the requested attribute
      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<Types...>>::type &
      getAttr(void)
      {
	return std::get<ct::getIdx<name, names...>()>(_values);
      }

      //! \brief Gets an attribute
      //! \tparam name the name of the requested attribute, must be declared as follow (in the global scope): \code constexpr char attrName[] = "attrName"; \endcode
      //! \return an lvalue reference to the constant requested attribute
      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<Types...>>::type const &
      getAttr(void) const
      {
	return std::get<ct::getIdx<name, names...>()>(_values);
      }

      //! \brief Sets an attribute by copy
      //! \tparam name the name of the requested attribute, must be declared as follow (in the global scope): \code constexpr char attrName[] = "attrName"; \endcode
      //! \param [in] v the new value
      template<char const * name>
      void
      setAttr(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<Types...>>::type const & v)
      {
	if (&v != &std::get<ct::getIdx<name, names...>()>(_values))
	  std::get<ct::getIdx<name, names...>()>(_values) = v;
      }

      //! \brief Sets an attribute by move
      //! \tparam name the name of the requested attribute, must be declared as follow (in the global scope): \code constexpr char attrName[] = "attrName"; \endcode
      //! \param [in] v the new value
      template<char const * name>
      void
      setAttr(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<Types...>>::type && v)
      {
	if (&v != &std::get<ct::getIdx<name, names...>()>(_values))
	  std::get<ct::getIdx<name, names...>()>(_values) = std::forward<typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<Types...>>::type>(v);
      }

      //! \brief Insert a Component into an output stream
      //! \param [out] os the output stream in which the given Component will be inserted
      //! \param [in] c the Component to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Component const & c)
      {
	os << '{';
	return c._print<names...>(os) << '}' << std::flush;
      }

    private:
      ID<ecs::Component>	_id;
      std::tuple<Types...>	_values;

    private:
      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component const & databaseComponent, std::true_type, Values&&... values) const;

      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component const &, std::false_type, Values&&... values) const;

      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component && databaseComponent, std::true_type, Values&&... values) const;

      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component &&, std::false_type, Values&&... values) const;

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<sizeof...(_names)>::type * = nullptr) const
      {
	os // << abi::__cxa_demangle(typeid(typename std::tuple_element<sizeof...(names) - sizeof...(_names) - 1, std::tuple<Types...>>::type).name(), nullptr, nullptr, nullptr) << ' '
	   << name << " = " << std::get<sizeof...(names) - sizeof...(_names) - 1>(_values) << "; ";
	return _print<_names...>(os);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<!sizeof...(_names)>::type * = nullptr) const
      {
	return os // << abi::__cxa_demangle(typeid(typename std::tuple_element<sizeof...(names) - sizeof...(_names) - 1, std::tuple<Types...>>::type).name(), nullptr, nullptr, nullptr) << ' '
		  << name << " = " << std::get<sizeof...(names) - 1>(_values);
      }
    };
  }
}

#include "DataBaseComponent.hpp"

namespace	entity_component_system
{
  namespace	component
  {
    template<typename... Types, char const *... names>
    Component<ct::TypesWrapper<Types...>, names...>::Component(database::Component const & databaseComponent) : _id(databaseComponent.getID()), _values(_initValues(databaseComponent, std::true_type())) {}

    template<typename... Types, char const *... names>
    Component<ct::TypesWrapper<Types...>, names...>::Component(database::Component && databaseComponent) : _id(databaseComponent.getID()), _values(_initValues(std::move(databaseComponent), std::true_type())) {}

    template<typename... Types, char const *... names>
    Component<ct::TypesWrapper<Types...>, names...> &
    Component<ct::TypesWrapper<Types...>, names...>::operator=(database::Component const & databaseComponent)
    {
      _id = databaseComponent.getID();
      _values = _initValues(databaseComponent, std::true_type());
      return *this;
    }

    template<typename... Types, char const *... names>
    Component<ct::TypesWrapper<Types...>, names...> &
    Component<ct::TypesWrapper<Types...>, names...>::operator=(database::Component && databaseComponent)
    {
      _id = databaseComponent.getID();
      _values = _initValues(std::move(databaseComponent), std::true_type());
      return *this;
    }

    template<typename... Types, char const *... names> template<typename... Values>
    std::tuple<Types...>
    Component<ct::TypesWrapper<Types...>, names...>::_initValues(database::Component const & databaseComponent, std::true_type, Values&&... values) const
    {
      return _initValues(databaseComponent,
			 std::integral_constant<bool, sizeof...(Values) + 1 < sizeof...(Types)>(),
			 std::forward<Values>(values)...,
			 databaseComponent.getAttr<typename std::tuple_element<sizeof...(Values), std::tuple<Types...>>::type>(std::get<sizeof...(Values)>(std::tuple<decltype(names)...>(names...))));
    }

    template<typename... Types, char const *... names> template<typename... Values>
    std::tuple<Types...>
    Component<ct::TypesWrapper<Types...>, names...>::_initValues(database::Component const &, std::false_type, Values&&... values) const
    {
      return std::forward_as_tuple(std::forward<Values>(values)...);
    }

    template<typename... Types, char const *... names> template<typename... Values>
    std::tuple<Types...>
    Component<ct::TypesWrapper<Types...>, names...>::_initValues(database::Component && databaseComponent, std::true_type, Values&&... values) const
    {
      return _initValues(std::move(databaseComponent),
			 std::integral_constant<bool, sizeof...(Values) + 1 < sizeof...(Types)>(),
			 std::forward<Values>(values)...,
			 std::move(databaseComponent.getAttr<typename std::tuple_element<sizeof...(Values), std::tuple<Types...>>::type>(std::get<sizeof...(Values)>(std::tuple<decltype(names)...>(names...)))));
    }

    template<typename... Types, char const *... names> template<typename... Values>
    std::tuple<Types...>
    Component<ct::TypesWrapper<Types...>, names...>::_initValues(database::Component &&, std::false_type, Values&&... values) const
    {
      return std::forward_as_tuple(std::forward<Values>(values)...);
    }
  }
}
