//
// ComponentTypeID.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 21:20:25 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 26 15:54:33 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
    //! \brief an enum representing all component types, and ending with 'ComponentTypesNb', giving the number of component types
    enum class	ComponentTypeID
      {
	BasicIdEntity,
	BasicUnsignedShort,
	Vector2Int,
	Vector2Unsigned,
	TestUnsigned,
	TestString,
	ComponentTypesNb
      };
  }
}
