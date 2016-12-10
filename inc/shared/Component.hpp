//
// Component.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 17:12:15 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 10 01:31:22 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <functional>
#include <string>
#include <tuple>
#include "DataBaseComponent.hpp"

namespace	entity_component_system
{
  namespace	component
  {
    //! \brief class used to define the types of the component's attributes
    template<typename...> struct	Types;

    //! \brief compile-time Component class (see its specialization below)
    template<typename, char const *...>
    class	Component;

    //! \brief compile-time Component class
    //!
    //! this class is designed to represent a component outside of the database
    //! \param [in] TypesWrapper (template parameter) the types of the component's attributes, wrapped in a templated class or struct such as entity_component_system::component::Types
    //! \param [in] Types (template parameter) the types of the component's attributes
    //! \param [in] names (template parameter) the names of the component's attributes, in the same order as the types are (must be variables with internal linkage, declared as follow: constexpr char var[] = "name";)
    template<template<typename...> class TypesWrapper, typename... Types, char const *... names>
    class	Component<TypesWrapper<Types...>, names...>
    {
      static constexpr bool	constantStringCompare(char const * const lhs, char const * const rhs)	{ return *lhs && *rhs ? *lhs == *rhs && constantStringCompare(lhs + 1, rhs + 1) : !*lhs && !*rhs; }

      template<unsigned idx, char const * s1, char const *... s>
      static constexpr unsigned
      _getIdx(std::true_type)
      {
	return idx - 1;
      }

      template<unsigned idx, char const *s1, char const *s2, char const *...s>
      static constexpr unsigned
      _getIdx(std::false_type)
      {
	return _getIdx<idx + 1, s1, s...>(std::integral_constant<bool, constantStringCompare(s1, s2)>());
      }

      template<char const * toFind, char const * ... list>
      static constexpr unsigned
      getIdx(void)
      {
	return _getIdx<0, toFind, list...>(std::false_type());
      }

    public:
      //! \brief Default constructor
      Component(void) : _values(Types()...) {}
      //! \brief Constructor
      //!
      //! allows you to initialize attributes by copy
      //! \param [in] values values to initialize attributes
      Component(Types const &... values) : _values(values...) {}
      //! \brief Constructor
      //!
      //! allows you to initialize attributes' by copy and/or move depending on the type of the value (lvalue or rvalue) passed as parameter when called
      //! \param [in] values values to initialize attributes
      Component(Types&&... values) : _values(std::forward<Types>(values)...) {}
      //! \brief Constructor
      //!
      //! initializes attributes by copy with corresponding databaseComponent's attributes values
      //! \param [in] databaseComponent a component used in database with at least the same attributes as the one's of the component being constructed
      Component(database::Component const & databaseComponent) : _values(_initValues(databaseComponent, std::true_type())) {}
      //! \brief Default copy constructor
      Component(Component const &) = default;
      //! \brief Default move constructor
      Component(Component &&) = default;
      //! \brief Destructor
      ~Component(void) {}

      //! \brief Gets an attribute
      //! \param [in] name (template parameter) the name of the attribute to get (must be a variable with internal linkage, declared as follow: constexpr char var[] = "name";)
      //! \return an lvalue reference to the requested attribute
      template<char const * name>
      typename std::tuple_element<getIdx<name, names...>(), std::tuple<Types...>>::type &
      getAttr(void)
      {
	return std::get<getIdx<name, names...>()>(_values);
      }

      //! \brief Gets an attribute
      //! \param [in] name (template parameter) the name of the attribute to get (must be a variable with internal linkage, declared as follow: constexpr char var[] = "name";)
      //! \return an lvalue reference to the constant requested attribute
      template<char const * name>
      typename std::tuple_element<getIdx<name, names...>(), std::tuple<Types...>>::type const &
      getAttr(void) const
      {
	return std::get<getIdx<name, names...>()>(_values);
      }

      //! \brief Sets an attribute by copy
      //! \param [in] name (template parameter) the name of the attribute to set (must be a variable with internal linkage, declared as follow: constexpr char var[] = "name";)
      //! \param [in] v the new value of the concerned attribute
      template<char const * name>
      void
      setAttr(typename std::tuple_element<getIdx<name, names...>(), std::tuple<Types...>>::type const & v)
      {
	std::get<getIdx<name, names...>()>(_values) = v;
      }

      //! \brief Sets an attribute by copy or move, depending on the type of the value (lvalue or rvalue) passed as parameter when called
      //! \param [in] name (template parameter) the name of the attribute to set (must be a variable with internal linkage, declared as follow: constexpr char var[] = "name";)
      //! \param [in] v the new value of the concerned attribute
      template<char const * name>
      void
      setAttr(typename std::tuple_element<getIdx<name, names...>(), std::tuple<Types...>>::type && v)
      {
	std::get<getIdx<name, names...>()>(_values) = std::forward<typename std::tuple_element<getIdx<name, names...>(), std::tuple<Types...>>::type>(v);
      }

      //! \brief Insert a component into an output stream
      //! \param [out] os the output stream in which the given component will be inserted
      //! \param [in] c the component to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Component const & c)
      {
	os << '{';
	return c._print<names...>(os) << '}' << std::flush;
      }

    private:
      std::tuple<Types...>		_values;

    private:
      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component const & databaseComponent, std::true_type, Values&&... values)
      {
	return _initValues(databaseComponent,
			   std::integral_constant<bool, sizeof...(Values) + 1 < sizeof...(Types)>(),
			   values...,
			   databaseComponent.getAttr<typename std::tuple_element<sizeof...(Values), std::tuple<Types...>>::type>(std::get<sizeof...(Values)>(std::tuple<decltype(names)...>(names...))));
      }

      template<typename... Values>
      std::tuple<Types...>
      _initValues(database::Component const &, std::false_type, Values&&... values)
      {
	return std::tuple<Types...>(values...);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<sizeof...(_names), void *>::type = 0) const
      {
	os << name << " => " << std::get<sizeof...(names) - sizeof...(_names) - 1>(_values) << "; ";
	return _print<_names...>(os);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<!sizeof...(_names), void *>::type = 0) const
      {
	return os << name << " => " << std::get<sizeof...(names) - 1>(_values);
      }
    };
  }
}

namespace	ecs = entity_component_system;
