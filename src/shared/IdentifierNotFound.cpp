//
// IdentifierNotFound.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 14:12:11 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec  7 14:18:13 2016 Victorien LE COUVIOUR--TUFFET
//

#include "IdentifierNotFound.hpp"

namespace	entity_component_system
{
  IdentifierNotFound::IdentifierNotFound(std::string const & id) noexcept : _what{0}
  {
    std::copy(id.begin(), id.end(), _what);
  }

  char const *	IdentifierNotFound::what(void) const noexcept	{ return _what; }
}
