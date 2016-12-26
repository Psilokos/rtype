//
// DataBaseComponent.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Nov 30 15:46:47 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 26 16:05:46 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include "BadType.hpp"
#include "CompileTime.hpp"
#include "ID.hpp"
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
    //! \brief Class representing a component in the database
    class	Component
    {
      class	Attribute;

    public:
      //! \brief Constructor defining the attributes
      //! \param [in] values a tuple containing the initial values of the attributes
      //! \param [in] names the names of the attributes, must be given in same order as the values in the tuple (can either be std::string or cstring)
      template<typename... AttrNames, typename... AttrTypes>
      Component(ID<ecs::Component> const & id, std::tuple<AttrTypes...> && values, AttrNames&&... names)
	: Component(id, ct::Indexer<sizeof...(names)>(), std::move(values), std::string(std::forward<AttrNames>(names))...) {}

    private:
      template<unsigned... i, typename... AttrNames, typename... AttrTypes>
      Component(ID<ecs::Component> const & id, ct::Index<i...> &&, std::tuple<AttrTypes...> && values, AttrNames&&... names)
	: _id(id),
	  _attributes({{std::forward<AttrNames>(names),
		  std::shared_ptr<Attribute>(new Attribute(std::forward<typename std::tuple_element<i, std::tuple<AttrTypes...>>::type>(std::get<i>(values))))}...}) {}

    public:
      //! \brief Constructor initializing the attributes by copy from a component::Component
      //! \param [in] c the source component
      template<typename... Types, char const *... names>
      Component(component::Component<ct::TypesWrapper<Types...>, names...> const & c);

      //! \brief Constructor initializing the attributes by move from a component::Component
      //! \param [in] c the source component
      template<typename... Types, char const *... names>
      Component(component::Component<ct::TypesWrapper<Types...>, names...> && c);

      //! \brief Default copy constructor
      Component(Component const &) = default;
      //! \brief Default move constructor
      Component(Component &&) = default;
      //! \brief Default destructor
      ~Component(void) {}

      //! \brief Assignement operator, setting the attributes by copy from a component::Component
      //! \param [in] c the source component
      //! \throw IdentifierNotFound if an attribute is not found in 'c'
      template<typename... Types, char const *... names>
      Component &	operator=(component::Component<ct::TypesWrapper<Types...>, names...> const & c);

      //! \brief Assignement operator, setting the attributes by move from a component::Component
      //! \param [in] c the source component
      //! \throw IdentifierNotFound if an attribute is not found in 'c'
      template<typename... Types, char const *... names>
      Component &	operator=(component::Component<ct::TypesWrapper<Types...>, names...> && c);

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

      //! \brief Checks if an attribute exists
      //! \param [in] name the name of the attribute to check
      //! \return true if the attribute exists, false otherwise
      bool	hasAttr(std::string const & name) { return _attributes.find(name) != _attributes.end(); }

      //! \brief Gets an attribute
      //! \tparam T the type of the attribute to get
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the requested attribute
      //! \throw IdentifierNotFound if the component does not exist
      //! \throw BadType if T is not the expected type
      template<typename T>
      T &
      getAttr(std::string const & name)
      {
	auto	it = _attributes.find(name);

	if (it == _attributes.end())
	  throw IdentifierNotFound(name);
	return it->second->value<T>(name);
      }

      //! \brief Gets an attribute
      //! \tparam T the type of the attribute to get
      //! \param [in] name the name of the attribute to get
      //! \return an lvalue reference to the constant requested attribute
      //! \throw IdentifierNotFound if the component does not exist
      //! \throw BadType if T is not the expected type
      template<typename T>
      T const &
      getAttr(std::string const & name) const
      {
	auto	it = _attributes.find(name);

	if (it == _attributes.end())
	  throw IdentifierNotFound(name);
	return it->second->value<T>(name);
      }

      //! \brief Sets an attribute by copy
      //! \tparam T the type of the attribute
      //! \param [in] name the name of the attribute to set
      //! \param [in] value the new value
      //! \throw IdentifierNotFound if the Component does not exist
      //! \throw BadType if 'T' is not the expected type
      template<typename T>
      void
      setAttr(std::string const & name, T const & value)
      {
	auto	it = _attributes.find(name);

	if (it == _attributes.end())
	  throw IdentifierNotFound(name);
	it->second->value<T>(name) = value;
      }

      //! \brief Sets an attribute by move
      //! \tparam T the type of the attribute
      //! \param [in] name the name of the attribute to set
      //! \param [in] value the new value
      //! \throw IdentifierNotFound if the Component does not exist
      //! \throw BadType if 'T' is not the expected type
      template<typename T>
      void
      setAttr(std::string const & name, T && value)
      {
	auto	it = _attributes.find(name);

	if (it == _attributes.end())
	  throw IdentifierNotFound(name);
	it->second->value<T>(name) = std::forward<T>(value);
      }

      //! \brief Insert a component into an output stream
      //! \param [out] os the output stream in which the given component will be inserted
      //! \param [in] c the component to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &
      operator<<(std::ostream & os, Component const & c)
      {
	auto	it = c._attributes.begin();

	os << '{';
	while (it != c._attributes.end())
	  {
	    os // << abi::__cxa_demangle(c._attributes[it->second]->type()->name(), nullptr, nullptr, nullptr) << ' '
	      << it->first << " = " << *it->second;
	    if (++it != c._attributes.end())
	      os << "; ";
	    else
	      os << '}';
	  }
	return os;
      }

    private:
      ID<ecs::Component>					_id;
      std::map<std::string, std::shared_ptr<Attribute>>		_attributes;

    private:
      class	Attribute
      {
	class	Base;

      public:
	template<typename T>
	Attribute(T const & value) : _attr(new Model<T>(value)) {}
	template<typename T>
	Attribute(T && value) : _attr(new Model<T>(std::forward<T>(value))) {}
	Attribute(Attribute const & src) : _attr(src._attr->copy()) {}
	Attribute(Attribute &&) = default;

	Attribute &	operator=(Attribute &&) = default;

	template<typename T>
	T &	value(std::string const & attrName) const { return *reinterpret_cast<T *>(_attr->value(attrName, typeid(T))); }

	std::type_info const *	type(void) const { return _attr->type(); }

	friend std::ostream &	operator<<(std::ostream & os, Attribute const & a) { return a._attr->dump(os); }

      private:
	std::unique_ptr<Base>	_attr;

      private:
	class	Base
	{
	public:
	  virtual ~Base(void) {}

	  virtual Base *	copy(void) const = 0;

	  virtual std::type_info const *	type(void) const = 0;
	  virtual void *			value(std::string const & attrName, std::type_info const & typeInfo) = 0;

	  virtual std::ostream &	dump(std::ostream & os) const = 0;
	};

	template<typename T>
	class	Model : public Base
	{
	public:
	  Model(T const & value) : _value(value), _typeInfo(&typeid(T)) {}
	  Model(T && value) : _value(std::forward<T>(value)), _typeInfo(&typeid(T)) {}
	  ~Model(void) {}

	  Model *	copy(void) const { return new Model(*this); }

	  std::type_info const *	type(void) const { return _typeInfo; }

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
      };

      template<char const *... names>
      class	_Assign
      {
      public:
	template<typename... Types>
	_Assign(component::Component<ct::TypesWrapper<Types...>, names...> const & c, std::map<std::string, std::shared_ptr<Attribute>> & attributes) { _setAttributes<0, names...>(c, attributes); }

	template<typename... Types>
	_Assign(component::Component<ct::TypesWrapper<Types...>, names...> && c, std::map<std::string, std::shared_ptr<Attribute>> & attributes) { _setAttributes<0, names...>(std::move(c), attributes); }

      private:
	template<unsigned idx, char const *, char const *..., typename... Types>
	void
	_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const &, std::map<std::string, std::shared_ptr<Attribute>> & attributes,
		       typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

	template<unsigned idx, typename... Types>
	void	_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const &, std::map<std::string, std::shared_ptr<Attribute>> &,
			       typename std::enable_if<idx == sizeof...(names)>::type * = nullptr) {}

	template<unsigned idx, char const *, char const *..., typename... Types>
	void
	_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> &&, std::map<std::string, std::shared_ptr<Attribute>> & attributes,
		       typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

	template<unsigned idx, typename... Types>
	void	_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> &&, std::map<std::string, std::shared_ptr<Attribute>> &,
			       typename std::enable_if<idx == sizeof...(names)>::type * = nullptr) {}
      };
    };
  }
}

#include "Component.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<typename... Types, char const *... names>
    Component::Component(component::Component<ct::TypesWrapper<Types...>, names...> const & c)
      : _id(c.getID()), _attributes({{names, std::shared_ptr<Attribute>(new Attribute(c.getAttr<names>()))}...}) {}

    template<typename... Types, char const *... names>
    Component::Component(component::Component<ct::TypesWrapper<Types...>, names...> && c)
      : _id(c.getID()), _attributes({{names, std::shared_ptr<Attribute>(new Attribute(std::move(c.getAttr<names>())))}...}) {}

    template<typename... Types, char const *... names>
    Component &
    Component::operator=(component::Component<ct::TypesWrapper<Types...>, names...> const & c)
    {
      _Assign<names...>	assign(c, _attributes);

      _id = c.getID();
      return *this;
    }

    template<typename... Types, char const *... names>
    Component &
    Component::operator=(component::Component<ct::TypesWrapper<Types...>, names...> && c)
    {
      _Assign<names...>	assign(std::move(c), _attributes);

      _id = c.getID();
      return *this;
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... Types>
    void
    Component::_Assign<names...>::_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> const & c,
						 std::map<std::string, std::shared_ptr<Attribute>> & attributes, typename std::enable_if<idx < sizeof...(names)>::type *)
    {
      auto	it = attributes.find(name);

      if (it == attributes.end())
	throw IdentifierNotFound(name);
      it->second->value<typename std::tuple_element<idx, std::tuple<Types...>>::type>(name) = c.getAttr<name>();
      _setAttributes<idx + 1, _names...>(c, attributes);
    }

    template<char const *... names> template<unsigned idx, char const * name, char const *... _names, typename... Types>
    void
    Component::_Assign<names...>::_setAttributes(component::Component<ct::TypesWrapper<Types...>, names...> && c,
						 std::map<std::string, std::shared_ptr<Attribute>> & attributes, typename std::enable_if<idx < sizeof...(names)>::type *)
    {
      auto	it = attributes.find(name);

      if (it == attributes.end())
	throw IdentifierNotFound(name);
      it->second->value<typename std::tuple_element<idx, std::tuple<Types...>>::type>(name) = std::move(c.getAttr<name>());
      _setAttributes<idx + 1, _names...>(std::move(c), attributes);
    }
  }
}
