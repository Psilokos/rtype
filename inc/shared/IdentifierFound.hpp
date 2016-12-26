//
// IdentifierFound.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec  6 16:43:20 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 12 16:00:55 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <stdexcept>

namespace	entity_component_system
{
  //! \brief Exception class
  //! Raised when a component is found while trying to add a new one with the same identifier
  class		IdentifierFound : public std::exception
  {
  public:
    //! \brief Constructor
    IdentifierFound(std::string const & id) noexcept;

    //! \brief get the error message
    //! \return a pointer to the constant error message
    char const *	what(void) const noexcept;

  private:
    char	_what[1024];
  };
}

namespace	ecs = entity_component_system;
