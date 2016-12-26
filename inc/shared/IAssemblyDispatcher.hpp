//
// IAssemblyDispatcher.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec 16 18:46:43 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 19 11:55:49 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <cstdint>
#include "AllAssemblies.hpp"
#include "IDispatcher.hpp"

namespace	entity_component_system::database
{
  class	IAssemblyDispatcher : public IDispatcher<Assemblies> {};
}
