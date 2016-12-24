//
// IDataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:44:29 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 24 15:28:42 2016 Victorien LE COUVIOUR--TUFFET
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
    //! \brief Database interface
    class		IDataBase
    {
    public:
      //! \brief Default destructor
      virtual ~IDataBase(void) = default;

      //! \brief Creates an empty entity
      //! \return the created entity's id
      virtual ID<ecs::Entity>	createEntity(void) = 0;

      //! \brief Creates an empty entity with a name
      //! \param [in] name the name of the new entity
      //! \return the created entity's id
      virtual ID<ecs::Entity>	createEntity(std::string const & name) = 0;

      //! \brief Creates an entity from an assembly
      //! \param [in,out] assembly the source assembly. The created entity's id is set in the assembly
      virtual void		createEntityFromAssembly(IAssembly & assembly) = 0;

      //! \brief Gets the name of an entity
      //! \param [in] id the entity's id
      //! \return the name of the requested entity
      virtual std::string	getEntityName(ID<ecs::Entity> const & id) const = 0;

      //! \brief Sets the name of an entity
      //! \param [in] id the entity's id
      //! \param [in] name
      virtual void		setEntityName(ID<ecs::Entity> const & id, std::string const & name) = 0;

      //! \brief Creates a component of the given type
      //! \param [in] componentTypeID the id corresponding to the component type to create
      //! \return the created component's id
      virtual ID<ecs::Component>	createComponent(ComponentTypeID const componentTypeID) = 0;

      //! \brief Creates a component of the given type and binds it to an entity
      //! \param [in] entityId the id of the entity in which will be bind the new component
      //! \param [in] componentTypeID the id corresponding to the component type to create
      //! \param [in] componentName the name of the component in the entity
      virtual ID<ecs::Component>	createAndBindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, std::string const & componentName) = 0;

      //! \brief Binds a component to an entity
      //! \param [in] entityId the id of the entity in which will be bind the component
      //! \param [in] componentTypeID the id corresponding to the component type to create
      //! \param [in] componentId the id of the component to bind
      //! \param [in] componentName the name of the component in the entity
      //! \return the componentId passed in parameter
      virtual ID<ecs::Component>	bindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, ID<ecs::Component> const & componentId, std::string const & componentName) = 0;

      //! \brief Gets an entity from its id
      //! \param [in] id the id of the entity to retrieve
      //! \return an Any instance containing an entity::RTEntity if found, nothing otherwise
      virtual Any				getEntity(ID<ecs::Entity> const & id) const = 0;

      //! \brief Gets a component from its id
      //! \param [in] id the id of the component to retrieve
      //! \return an Any instance containing a Component if found, nothing otherwise
      virtual Any				getComponent(ID<ecs::Component> const & id) const = 0;

      //! \brief Gets a component from its id and its entity's id
      //! \param [in] entityId the id of the entity in which the component is stored
      //! \param [in] componentId the id of the component to retrieve
      //! \return an Any instance containing a Component if found, nothing otherwise
      virtual Any				getComponentFromEntity(ID<ecs::Entity> const & entityId, ID<ecs::Component> const & componentId) const = 0;

      //! \brief Gets all entities having a component named 'componentName'
      //! \param [in] componentName the name of a component
      //! \return a list with all matching entities
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(std::string const & componentName) const = 0;

      //! \brief Gets all entities having a component of type 'componentTypeID'
      //! \param [in] componentTypeID the type of a component
      //! \return a list with all matching entities
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(ComponentTypeID const componentTypeID) const = 0;

      //! \brief Gets all entities having a component of type 'componentTypeID' named 'componentName'
      //! \param [in] componentName the name of a component
      //! \param [in] componentTypeID the type of a component
      //! \return a list with all matching entities
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponent(std::string const & componentName, ComponentTypeID const componentTypeID) const = 0;

      //! \brief Gets all entities with a component being equal to 'value'
      //! \param [in] componentTypeID the type of the compared component
      //! \param [in] value the component value to compare
      //! \return a list with all matching entities
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponentEqualTo(ComponentTypeID const componentTypeID, Component const & value) const = 0;

      //! \brief Gets all entities with a component being equal to 'value' and named 'componentName'
      //! \param [in] componentName the name of the component to compare
      //! \param [in] componentTypeID the type of the compared component
      //! \param [in] value the component value to compare
      //! \return a list with all matching entities
      virtual std::list<entity::RTEntity>	getAllEntitiesWithComponentEqualTo(std::string const & componentName, ComponentTypeID const componentTypeID, Component const & value) const = 0;

      //! \brief Sets an entity
      //! \param [in] entities the entity to set
      virtual void		setEntity(entity::RTEntity const & entity) = 0; // upgrade to auto detection of new components (automatic type detection)

      //! \brief Sets a list of entity
      //! \param [in] entities the list of entity to set
      virtual void		setEntities(std::vector<entity::RTEntity> const & entities) = 0;

      //! \brief Sets a component
      //! \param [in] entityId the entity in which the component belong
      //! \param [in] component the component to set
      virtual void		setComponent(ID<ecs::Entity> const & entityId, Component const & component) = 0;

      //! \brief Gets all changed components since last call
      //! \return a list of pair with, as first element, the id of the entity to which the component is bind, as second, the type ID of the component, and as third, the component within an Any object
      virtual std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>	getLastChanges(void) = 0;

      //! \brief Gets all changed components since last call
      //! \return a list of pair with, as first element, the id of the entity to which the component is bind, as second, the type ID of the component, and as third, the component within an Any object
      virtual std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>	getLastChangesWithAttr(std::string const & attrName) = 0;
    };
  }
}

namespace	ecs = entity_component_system;
