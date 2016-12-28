//
// HMacGenerator.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:43:12 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec 27 23:37:57 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "AllAssemblies.hpp"
#include "ISystem.hpp"

namespace	entity_component_system
{
  namespace	system
  {
    class	HMacGenerator : public ISystem
    {
    public:
      HMacGenerator(database::IDataBase & db);
      HMacGenerator(HMacGenerator const &) = delete;
      HMacGenerator(HMacGenerator &&) = delete;
      virtual ~HMacGenerator(void) = default;

      virtual void	update(database::IDataBase & db);

    private:
      void	_hmacSha1(entity::HMAC & hmac);
    };
  }
}
