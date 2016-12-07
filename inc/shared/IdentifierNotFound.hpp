//
// IdentifierNotFound.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec  6 16:43:20 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec  6 17:32:49 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <stdexcept>

namespace	entity_component_system
{
  //! \brief Exception class
  //! Raised when a component / attribute is not found while accessing it from an entity / component, respectively
  class		IdentifierNotFound : public std::exception
  {
  public:
    //! \brief Constructor
    IdentifierNotFound(std::string const & id) noexcept;

    //! \brief get the error message
    //! \return the missing identifier
    char const *	what(void) const noexcept;

  private:
    char	_what[1024];
  };
}

namespace	ecs = entity_component_system;
