//
// Component.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Nov 30 15:46:47 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec  7 14:46:07 2016 Victorien LE COUVIOUR--TUFFET
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

namespace	entity_component_system
{
  namespace	component
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
	  T			_value;
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

      //! \brief Default copy assignement operator
      Component &	operator=(Component const &) = default;
      //! \brief Default move assignement operator
      Component &	operator=(Component &&) = default;

      //! \brief Check if a component exists
      //! \param [in] name the name of the attribute to check
      //! \return true if the attribute exists, false otherwise
      bool	hasAttr(std::string const & name) { return _namesIdxMap.find(name) != _namesIdxMap.end(); }

      //! \brief Get an attribute
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the requested attribute if found, raises an ecs::IdentifierNotFound exception otherwise
      template<typename T> T &		getAttr(std::string const & name)	{ return _attributes[_namesIdxMap.at(name)]->value<T>(name); }

      //! \brief Get an attribute
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the constant requested attribute if found, raises an ecs::IdentifierNotFound exception otherwise
      template<typename T> T const &	getAttr(std::string const & name) const	{ return _attributes[_namesIdxMap.at(name)]->value<T>(name); }

      //! \brief Set an attribute
      //! \param [in] name the name of the attribute to set
      //! \param [in] value the value of the attribute to set
      template<typename T>
      void	setAttr(std::string const & name, T && value)
      {
	if (_namesIdxMap.find(name) == _namesIdxMap.end())
	  {
	    _namesIdxMap.emplace(name, _attributes.size());
	    _attributes.emplace(_attributes.end(), std::shared_ptr<Attribute>(new Attribute(std::forward<T>(value))));
	  }
	else
	  _attributes[_namesIdxMap[name]]->value<T>(name) = value;
      }

      //! \brief Removes an attribute
      //! \param [in] name the name of the attribute to remove
      //! \return a shallow copy of the removed attribute
      template<typename T>
      T		delAttr(std::string const & name)
      {
	T const		attr = this->getAttr<T>(name);
	unsigned const	idx = _namesIdxMap.at(name);

	_attributes.erase(_attributes.begin() + idx);
	_namesIdxMap.erase(name);
	for (auto & pair : _namesIdxMap)
	  if (pair.second > idx)
	    --pair.second;
	return attr;
      }

      //! \brief Removes an attribute
      //! \param [in] name the name of the attribute to remove
      void	delAttr(std::string const & name)
      {
	unsigned const	idx = _namesIdxMap.at(name);

	_attributes.erase(_attributes.begin() + idx);
	_namesIdxMap.erase(name);
	for (auto & pair : _namesIdxMap)
	  if (pair.second > idx)
	    --pair.second;
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
