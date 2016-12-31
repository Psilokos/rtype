//
// ISystem.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:21:10 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 31 18:23:04 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "IDataBase.hpp"

namespace	entity_component_system
{
  namespace	system
  {
    class	ISystem
    {
    public:
      virtual ~ISystem(void) = default;

      virtual void	update(database::IDataBase & db) = 0;
    };
  }
}
