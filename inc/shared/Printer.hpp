//
// Printer.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:43:12 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 01:07:52 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "ISystem.hpp"

namespace	entity_component_system
{
  namespace	system
  {
    class	Printer : public ISystem
    {
    public:
      Printer(void) = default;
      Printer(Printer const &) = delete;
      Printer(Printer &&) = delete;
      virtual ~Printer(void) = default;

      virtual void	update(database::IDataBase & db);
    };
  }
}
