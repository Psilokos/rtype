//
// DataBaseComponent.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Nov 30 15:46:47 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 00:44:09 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <cxxabi.h>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <tuple>
#include <vector>
#include "CompileTime.hpp"
#include "IdentifierNotFound.hpp"

namespace	entity_component_system
{
  namespace	component
  {
    template<typename, char const *...>
    class	Component;

    template<typename... Types, char const *... names>
    class	Component<ct::TypesWrapper<Types...>, names...>;
  }

  namespace	database
  {
    //! \brief Generic class for all components
    class	Component
    {
      class	Attribute
      {
      public:
	//! \brief Exception class
	//! Raised when an attribute's type is not the expected one, when trying to retrieve it
	class	BadType : public std::bad_cast
	{
	public:
	  //! \brief Constructor
	  //! \param [in] attrName the name of the requested attribute
	  //! \param [in] goodTypeInfo a pointer to a type_info, representing the expected type
	  //! \param [in] goodTypeInfo a pointer to a type_info, representing the given type
	  BadType(std::string const & attrName, std::type_info const * goodTypeInfo, std::type_info const * badTypeInfo) : _what{0}
	  {
	    std::string	tmp = attrName
	      + " expected type was '"
	      + abi::__cxa_demangle(goodTypeInfo->name(), nullptr, nullptr, nullptr)
	      + "', got '"
	      + abi::__cxa_demangle(badTypeInfo->name(), nullptr, nullptr, nullptr)
	      + "' instead.";

	    std::copy(tmp.begin(), tmp.end(), _what);
	  }

	  //! \brief get the error message
	  //! \return a pointer to the constant error message
	  char const *	what(void) const noexcept	{ return _what; }

	private:
	  char			_what[1024];
	};

      private:
	class	Base
	{
	public:
	  virtual ~Base(void) {}

	  virtual Base *	copy(void) const = 0;

	  virtual void *	value(std::string const & attrName, std::type_info const & typeInfo) = 0;

	  virtual std::ostream &	dump(std::ostream & os) const = 0;
	};

	template<typename T>
	class	Model : public Base
	{
	public:
	  Model(T && value) : _value(std::forward<T>(value)), _typeInfo(&typeid(T)) {}
	  ~Model(void) {}

	  Model *	copy(void) const { return new Model(*this); }

	  void *	value(std::string const & attrName, std::type_info const & typeInfo)
	  {
	    if (typeInfo != *_typeInfo)
	      throw BadType(attrName, _typeInfo, &typeInfo);
	    return reinterpret_cast<void *>(&_value);
	  }

	  std::ostream &	dump(std::ostream & os) const	{ return os << _value; }

	private:
	  T				_value;
	  std::type_info const *	_typeInfo;
	};

      public:
	template<typename T>
	Attribute(T && value) : _attr(new Model<T>(std::forward<T>(value))) {}
	Attribute(Attribute const & src) : _attr(src._attr->copy()) {}
	Attribute(Attribute &&) = default;

	Attribute &	operator=(Attribute &&) = default;

	template<typename T>
	T &	value(std::string const & attrName) const { return *reinterpret_cast<T *>(_attr->value(attrName, typeid(T))); }

	friend std::ostream &	operator<<(std::ostream & os, Attribute const & a) { return a._attr->dump(os); }

      private:
	std::unique_ptr<Base>	_attr;
      };

    public:
      //! \brief Construstor
      //! \param [in] values a tuple containing the initial values of the attributes and their types
      //! \param [in] names the names of the attributes (must be in the same order as the values in the tuple)
      template<typename... AttrNames, typename... AttrTypes>
      Component(std::tuple<AttrTypes...> && values, AttrNames&&... names) : Component(values, 0, names...) {}

    private:
      template<typename... AttrNames, typename... AttrTypes>
      Component(std::tuple<AttrTypes...> & values, unsigned i, AttrNames&&... names) : _namesIdxMap({{names, i++}...}), _attributes(_getAttributes<AttrTypes...>(values)) {}

    public:
      //! \brief Default copy constructor
      Component(Component const &) = default;
      //! \brief Default move constructor
      Component(Component &&) = default;
      //! \brief Default destructor
      ~Component(void) {}

      template<typename... Types, char const *... names>
      Component &
      operator=(component::Component<ct::TypesWrapper<Types...>, names...> const & c)
      {
	_Assign<names...>	assign(c, _namesIdxMap, _attributes);

	return *this;
      }

      //! \brief Default copy assignement operator
      Component &	operator=(Component const &) = default;
      //! \brief Default move assignement operator
      Component &	operator=(Component &&) = default;

      //! \brief Check if a component exists
      //! \param [in] name the name of the attribute to check
      //! \return true if the attribute exists, false otherwise
      bool	hasAttr(std::string const & name) { return _namesIdxMap.find(name) != _namesIdxMap.end(); }

      //! \brief Get an attribute
      //!
      //! If the given type 'T' is not the expected one, an entity_component_system::database::Component::Attribute::BadType exception is raised
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the requested attribute if found, raises an ecs::IdentifierNotFound exception otherwise
      template<typename T>
      T &
      getAttr(std::string const & name)
      {
	if (_namesIdxMap.find(name) == _namesIdxMap.end())
	  throw IdentifierNotFound(name);
	return _attributes[_namesIdxMap.at(name)]->value<T>(name);
      }

      //! \brief Get an attribute
      //!
      //! If the given type 'T' is not the expected one, an entity_component_system::database::Component::Attribute::BadType exception is raised
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the constant requested attribute if found, raises an ecs::IdentifierNotFound exception otherwise
      template<typename T>
      T const &
      getAttr(std::string const & name) const
      {
	if (_namesIdxMap.find(name) == _namesIdxMap.end())
	  throw IdentifierNotFound(name);
	return _attributes[_namesIdxMap.at(name)]->value<T>(name);
      }

      //! \brief Set an attribute
      //!
      //! If the attribute is not found, then an IdentifierNotFound exception is raised
      //!
      //! If the given type 'T' is not the expected one, an entity_component_system::database::Component::Attribute::BadType exception is raised
      //! \param [in] name the name of the attribute to set
      //! \param [in] value the value of the attribute to set
      template<typename T>
      void	setAttr(std::string const & name, T && value)
      {
	if (_namesIdxMap.find(name) == _namesIdxMap.end())
	  throw IdentifierNotFound(name);
	_attributes[_namesIdxMap[name]]->value<T>(name) = value;
      }

      //! \brief Insert a component into an output stream
      //! \param [out] os the output stream in which the given component will be inserted
      //! \param [in] c the component to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, Component const & c)
      {
	for (auto & pair : c._namesIdxMap)
	  os << "\t\t" << pair.first << " => " << *c._attributes[pair.second] << std::endl;
	return os;
      }

    private:
      std::map<std::string, unsigned>		_namesIdxMap;
      std::vector<std::shared_ptr<Attribute>>	_attributes;

      template<char const *... names>
      struct	_Assign
      {
	template<typename... Types>
	_Assign(component::Component<ct::TypesWrapper<Types...>, names...> const & c, std::map<std::string, unsigned> const & namesIdxMap, std::vector<std::shared_ptr<Attribute>> & attributes)
	{
	  this->setAttributes<0, names...>(c, namesIdxMap, attributes);
	}

	template<unsigned idx, char const *, char const *..., typename... Types>
	void
	setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const &, std::map<std::string, unsigned> const &,
		      std::vector<std::shared_ptr<Attribute>> &, typename std::enable_if<idx < sizeof...(names), void *>::type = 0);

	template<unsigned idx, typename... Types>
	void
	setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const &, std::map<std::string, unsigned> const &,
		      std::vector<std::shared_ptr<Attribute>> &, typename std::enable_if<idx == sizeof...(names), void *>::type = 0)
	{}
      };

    private:
      template<typename... AttrTypes, typename... Attr>
      std::vector<std::shared_ptr<Attribute>>
      _getAttributes(std::tuple<AttrTypes...> & values, Attr... attr)
      {
	return _getAttributesImpl<AttrTypes...>(std::integral_constant<bool, sizeof...(Attr) < sizeof...(AttrTypes)>(), values, attr...);
      }

      template<typename... AttrTypes, typename... Attr>
      std::vector<std::shared_ptr<Attribute>>
      _getAttributesImpl(std::true_type, std::tuple<AttrTypes...> & values, Attr... attr)
      {
	return _getAttributes<AttrTypes...>(values, attr..., std::shared_ptr<Attribute>(new Attribute(std::move(std::get<sizeof...(attr)>(values)))));
      }

      template<typename... AttrTypes, typename... Attr>
      std::vector<std::shared_ptr<Attribute>>
      _getAttributesImpl(std::false_type, std::tuple<AttrTypes...> &, Attr... attr)
      {
	return std::vector<std::shared_ptr<Attribute>>({attr...});
      }
    };
  }
}

namespace	ecs = entity_component_system;

#include "Component.hpp"

template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... Types>
void
entity_component_system::database::Component::_Assign<names...>::setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const & c, std::map<std::string, unsigned> const & namesIdxMap,
									       std::vector<std::shared_ptr<Attribute>> & attributes, typename std::enable_if<idx < sizeof...(names), void *>::type)
{
  if (namesIdxMap.find(name) == namesIdxMap.end())
    throw IdentifierNotFound(name);
  attributes[namesIdxMap.at(name)]->value<typename std::tuple_element<idx, std::tuple<Types...>>::type>(name) = c.getAttr<name>();
  this->setAttributes<idx + 1, _names...>(c, namesIdxMap, attributes);
}
