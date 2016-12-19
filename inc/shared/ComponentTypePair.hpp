//
// ComponentTypePair.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 19:42:28 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 21:16:13 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
    enum class	ComponentTypeID;

    template<ComponentTypeID componentType, typename Component>
    struct	ComponentTypePair
    {
      static constexpr ComponentTypeID	typeID = componentType;

      typedef Component		Type;
    };
  }
}
