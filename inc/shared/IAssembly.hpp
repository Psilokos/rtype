//
// IAssembly.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec 16 17:08:43 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 14:43:30 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
    class	IAssemblyDispatcher;

    class	IAssembly
    {
    public:
      virtual void	visit(IAssemblyDispatcher & dsp) = 0;
    };
  }
}
