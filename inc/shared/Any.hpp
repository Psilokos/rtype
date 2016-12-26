//
// Any.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sun Dec 18 19:16:36 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 26 16:10:38 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <algorithm>
#include <cxxabi.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

class	Any
{
public:
  class	BadType : public std::bad_cast
  {
  public:
    //! \brief Constructor
    //! \param [in] goodTypeInfo a pointer to a type_info, representing the expected type
    //! \param [in] badTypeInfo a pointer to a type_info, representing the given type
    BadType(std::type_info const * goodTypeInfo, std::type_info const * badTypeInfo) : _what{0}
    {
      std::string	tmp = std::string("Any::getValue expected type was '")
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
    char			_what[2048];
  };

private:
  class		Value
  {
    class	Base;

  public:
    Value(void) = default;

    template<typename T>
    Value(T const & value) : _value(new Model<T>(value)) {}

    template<typename T>
    Value(T && value) : _value(new Model<T>(std::forward<T>(value))) {}

    Value(Value const & src) : _value(src._value ? src._value->copy() : nullptr) {}
    Value(Value && src) : _value(src._value ? src._value->move() : nullptr) {}

    Value &
    operator=(Value const & src)
    {
      if (this != &src)
	_value = std::unique_ptr<Base>(src._value ? src._value->copy() : nullptr);
      return *this;
    }

    Value &
    operator=(Value && src)
    {
      if (this != &src)
	_value = std::unique_ptr<Base>(src._value ? src._value->move() : nullptr);
      return *this;
    }

    operator bool(void) const { return _value != nullptr; }

    template<typename T>
    T &		value(void) const { return *reinterpret_cast<T *>(_value->value(typeid(T))); }

    std::type_info const *
    type(void) const
    {
      if (_value)
	return _value->type();
      return &typeid(void);
    }

    friend std::ostream &	operator<<(std::ostream & os, Value const & v) { return v._value->dump(os); }

  private:
    std::unique_ptr<Base>	_value;

  private:
    class	Base
    {
    public:
      virtual ~Base(void) {}

      virtual Base *	copy(void) const = 0;
      virtual Base *	move(void) = 0;

      virtual std::type_info const *	type(void) const = 0;
      virtual void *			value(std::type_info const & typeInfo) = 0;

      virtual std::ostream &	dump(std::ostream & os) const = 0;
    };

    template<typename T>
    class	Model : public Base
    {
    public:
      Model(typename std::decay<T>::type const & value) : _value(value), _typeInfo(&typeid(typename std::decay<T>::type)) {}
      Model(typename std::decay<T>::type && value) : _value(std::forward<T>(value)), _typeInfo(&typeid(typename std::decay<T>::type)) {}
      Model(Model const &) = default;
      Model(Model &&) = default;
      ~Model(void) {}

      Model *	copy(void) const	{ return new Model(*this); }
      Model *	move(void)		{ return new Model(std::move(*this)); }

      std::type_info const *	type(void) const { return _typeInfo; }

      void *	value(std::type_info const & typeInfo)
      {
	if (typeInfo != *_typeInfo)
	  throw BadType(_typeInfo, &typeInfo);
	return reinterpret_cast<void *>(&_value);
      }

      std::ostream &	dump(std::ostream & os) const	{ return os << _value; }

    private:
      typename std::decay<T>::type	_value;
      std::type_info const *		_typeInfo;
    };
  };

public:
  //! \brief Default constructor
  Any(void) = default;

  //! \brief Default copy constructor
  Any(Any const &) = default;

  //! \brief Default move constructor
  Any(Any &&) = default;

  //! \brief Constructor storing a value by copy
  //! \tparam ValueType the type of the value to store
  //! \param [in] v the value to store by copy
  template<typename ValueType>
  Any(ValueType const & v) : _v(v) {}

  //! \brief Constructor storing a value by move
  //! \tparam ValueType the type of the value to store
  //! \param [in] v the value to store by move
  template<typename ValueType>
  Any(ValueType && v) : _v(std::forward<ValueType>(v)) {}

  //! \brief Default destructor
  ~Any(void) = default;

  //! \brief Default copy assignement operator
  Any &	operator=(Any const &) = default;

  //! \brief Default move assignement operator
  Any &	operator=(Any &&) = default;

  //! \brief Checks if a value is stored
  //! \return true if a value is stored, false otherwise
  bool	hasValue(void) const	{ return _v; }

  //! \brief Gets the type of the stored value
  //! \return the type of the stored value if any, typeid(void) otherwise
  std::type_info const &	type(void) const { return *_v.type(); }

  //! \brief Gets the value stored by copy
  //! \tparam ValueType the type of the stored value
  //! \return a copy of the stored value
  template<typename ValueType>
  typename std::decay<ValueType>::type		getValue(void) const { return _v.value<typename std::decay<ValueType>::type>(); }

  //! \brief Gets the value stored by reference
  //! \tparam ValueType the type of the stored value
  //! \return a reference to the stored value
  template<typename ValueType>
  typename std::decay<ValueType>::type &	getValueByRef(void) const { return _v.value<typename std::decay<ValueType>::type>(); }

private:
  Value		_v;
};
