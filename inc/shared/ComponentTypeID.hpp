//
// ComponentTypeID.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 21:20:25 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 21 14:20:22 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
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