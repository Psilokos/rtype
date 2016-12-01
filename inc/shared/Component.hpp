//
// Component.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Nov 30 15:46:47 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec  1 20:14:54 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <initializer_list>
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
    class	Attribute
    {
  public:
      class	BadType : public std::bad_cast
      {
      public:
	BadType(std::string const & attrName, std::type_info const * goodTypeInfo, std::type_info const * badTypeInfo) : _what{0}
	{
	  std::string	tmp = attrName + " expected type was " + goodTypeInfo->name() + ", got " + badTypeInfo->name() + " instead.";

	  std::copy(tmp.begin(), tmp.end(), _what);
	}

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
      };

      template<typename T>
      class	Model : public Base
      {
      public:
	Model(T && value) : _value(value), _typeInfo(&typeid(T)) {}
	~Model(void) {}

	Model *	copy(void) const { return new Model(*this); }

	void *	value(std::string const & attrName, std::type_info const & typeInfo)
	{
	  if (typeInfo != *_typeInfo)
	    throw BadType(attrName, _typeInfo, &typeInfo);
	  return reinterpret_cast<void *>(&_value);
	}

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

    private:
      std::unique_ptr<Base>	_attr;
    };

    class	Component
    {
    public:
      template<typename... AttrNames, typename... AttrTypes>
      Component(std::tuple<AttrTypes...> && values, AttrNames&&... names) : Component(values, 0, names...) {}

    private:
      template<typename... AttrNames, typename... AttrTypes>
      Component(std::tuple<AttrTypes...> & values, unsigned i, AttrNames&&... names) : _namesIdxMap({{names, i++}...}), _attributes(_getAttributes<AttrTypes...>(values)) {}

    public:
      Component(Component const &) = default;
      Component(Component &&) = default;
      ~Component(void)
      {
	for (auto & attr : _attributes)
	  delete attr;
      }

      Component &	operator=(Component const &) = default;
      Component &	operator=(Component &&) = default;

      template<typename T>
      T &	attribute(std::string const & name) const	{ return _attributes[_namesIdxMap.at(name)]->value<T>(name); }

    private:
      std::map<std::string, unsigned>	_namesIdxMap;
      std::vector<Attribute*>		_attributes;

      template<typename... AttrTypes, typename... Attr>
      std::vector<Attribute*>
      _getAttributes(std::tuple<AttrTypes...> & values, Attr... attr)
      {
	return _getAttributesImpl<AttrTypes...>(std::integral_constant<bool, sizeof...(Attr) < sizeof...(AttrTypes)>(), values, attr...);
      }

      template<typename... AttrTypes, typename... Attr>
      std::vector<Attribute*>
      _getAttributesImpl(std::true_type, std::tuple<AttrTypes...> & values, Attr... attr)
      {
	return _getAttributes<AttrTypes...>(values, attr..., new Attribute(std::get<sizeof...(attr)>(values)));
      }

      template<typename... AttrTypes, typename... Attr>
      std::vector<Attribute*>
      _getAttributesImpl(std::false_type, std::tuple<AttrTypes...> & values, Attr... attr)
      {
	return std::vector<Attribute*>({attr...});
      }
    };
  }
}

namespace	ecs = entity_component_system;
