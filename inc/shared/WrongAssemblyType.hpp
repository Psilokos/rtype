//
// WrongAssemblyType.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec 21 21:28:33 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 21 21:42:27 2016 Victorien LE COUVIOUR--TUFFET
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
  //! Raised when ecs::database::DataBase::createEntityFromAssembly is called with a non-assembly type parameter
  class		WrongAssemblyType : public std::exception
  {
  public:
    //! \brief Constructor
    //! \param [in] typeInfo the typeInfo of the non-assembly type parameter
    WrongAssemblyType(std::type_info const & typeInfo) : _what{0}
    {
      std::string	tmp = std::string("The following type is not an assembly:\n'")
	+ abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, nullptr)
	+ "'.\nCheck your ecs::database::Assemblies type definition (AllAssemblies.hpp).";

      std::copy(tmp.begin(), tmp.end(), _what);
    }

    //! \brief get the error message
    //! \return a pointer to the constant error message
    char const *	what(void) const noexcept	{ return _what; }

  private:
    char			_what[2048];
  };
}
