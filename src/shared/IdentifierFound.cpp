//
// IdentifierFound.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Wed Dec  7 14:12:11 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 12 16:00:18 2016 Victorien LE COUVIOUR--TUFFET
//

#include "IdentifierFound.hpp"

namespace	entity_component_system
{
  IdentifierFound::IdentifierFound(std::string const & id) noexcept : _what{0}
  {
    std::copy(id.begin(), id.end(), _what);
  }

  char const *	IdentifierFound::what(void) const noexcept { return _what; }
}
