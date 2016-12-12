//
// BadType.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Dec 12 15:13:58 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 12 15:58:38 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <algorithm>
#include <cxxabi.h>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace	entity_component_system
{
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
    char			_what[2048];
  };
}
