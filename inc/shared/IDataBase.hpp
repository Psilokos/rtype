//
// IDataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:44:29 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 19 02:40:11 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <list>
#include <vector>
#include "Any.hpp"
#include "ComponentTypeID.hpp"
#include "IAssembly.hpp"
#include "ID.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    class		IDataBase
    {
    public:
      virtual ~IDataBase(void) {}

      virtual ID<ecs::Entity>	createEntity(void) = 0;
      virtual ID<ecs::Entity>	createEntity(std::string const & name) = 0;
      virtual void		createEntityFromAssembly(IAssembly & assembly) = 0;

      virtual std::string	getEntityName(ID<ecs::Entity> const & id) const = 0;
      virtual void		setEntityName(ID<ecs::Entity> const & id, std::string const & name) = 0;

      virtual ID<ecs::Component>	createComponent(ComponentTypeID const componentTypeID) = 0;
      virtual ID<ecs::Component>	createAndBindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, std::string const & componentName) = 0;

      virtual ID<ecs::Component>	bindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, ID<ecs::Component> const & componentId, std::string const & componentName) = 0;

      virtual Any				getEntity(ID<ecs::Entity> const & id) const = 0;
      virtual Any				getComponent(ID<ecs::Component> const & id) const = 0;
      virtual Any				getComponentFromEntity(ID<ecs::Entity> const & entityId, ID<ecs::Component> const & componentId) const = 0;
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(std::string const & componentName) const = 0;
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(ComponentTypeID const componentTypeID) const = 0;
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(std::string const & componentName, ComponentTypeID const componentTypeID) const = 0;
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponentEqualTo(ComponentTypeID const componentTypeID, Component const & value) const = 0;
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponentEqualTo(std::string const & componentName, ComponentTypeID const componentTypeID, Component const & value) const = 0;

      // virtual void		setEntity(ID<ecs::Entity> const & id, entity::RTEntity const & entity) = 0;
      // virtual void		setEntities(std::vector<std::pair<ID<Entity>, stde::any>> const & entities) = 0;
      // virtual void		setComponent(ID<ecs::Entity> const & entityI, Component const & component) = 0;
    };
  }
}

namespace	ecs = entity_component_system;
