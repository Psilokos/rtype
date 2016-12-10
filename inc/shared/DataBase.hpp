//
// DataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:30:40 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec  7 17:00:04 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "IDataBase.hpp"

namespace	ecs
{
  namespace	database
  {
    template<unsigned const componentTypeNb>
    class		DataBase : public IDataBase
    {
    public:
      DataBase(void);
      DataBase(DataBase const &) = delete;
      ~DataBase(void);

      DataBase &	operator=(DataBase const &) = delete;

      ID<Entity>	createEntity(EntityType const entityType);
      ID<Entity>	createAndAssembleEntity(EntityType const entityType, AssemblyType const assemblyType);
      ID<Component>	createComponent(ComponentType const componentType);
      ID<Component>	createAndBindComponent(ComponentType const componentType, ID<Entity> const & entityId);

    private:
      std::array<std::vector<>, componentTypeNb + 5>
    };
  }
}
