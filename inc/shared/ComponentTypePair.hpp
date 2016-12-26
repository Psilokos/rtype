//
// ComponentTypePair.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 19:42:28 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 26 15:56:33 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
    enum class	ComponentTypeID;

    //! \brief A pair attaching a component type to an enum value of ComponentTypeID
    //! \tparam componentType the enum value
    //! \tparam Component the component type
    template<ComponentTypeID componentType, typename Component>
    struct	ComponentTypePair
    {
      //! \brief the enum value
      static constexpr ComponentTypeID	typeID = componentType;

      //! \brief the component type
      typedef Component		Type;
    };
  }
}
