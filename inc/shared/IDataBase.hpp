//
// IDataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:44:29 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Nov 30 16:19:08 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <experimental/any>
#include <vector>

namespace	stde = std::experimental;

namespace	entity_component_system
{
  struct	Entity;
  struct	Component;

  namespace	database
  {
    template<typename T> class	ID;

    template<typename EntityType, typename ComponentType, typename AssemblyType>
    class		IDataBase
    {
    public:
      virtual ~IDataBase(void) {}

      virtual ID<Entity>	createEntity(EntityType const entityType) = 0;
      virtual ID<Entity>	createAndAssembleEntity(EntityType const entityType, AssemblyType const assemblyType) = 0;
      virtual ID<Component>	createComponent(ComponentType const componentType, unsigned const attrNb) = 0;
      virtual ID<Component>	createAndBindComponent(ComponentType const componentType, ID<Entity> const & entityId) = 0;

      virtual void		bindComponentToAssembly(AssemblyType const assemblyType, ComponentType const componentType) = 0;
      virtual ID<Component>	bindComponentToEntity(ID<Entity> const & entityId, ComponentType const componentType, ID<Component> const & componentId) = 0;

      virtual stde::any		getEntity(ID<Entity> const & id, std::list<ComponentType> const & components) const = 0;
      virtual stde::any		getComponentInEntity(ID<Entity> const & id, ComponentType const componentType) const = 0;
      virtual stde::any		getAllEntities(EntityType const entityType) const = 0;
      virtual stde::any		getEntityWithComponentEqualTo(ComponentType const componentType, stde::any const & value) const = 0;

      virtual void		setEntity(ID<Entity> const & id, stde::any const & entity) = 0;
      virtual void		setEntities(std::vector<std::pair<ID<Entity>, stde::any>> const & entities) = 0;
      virtual void		setComponent(ID<Entity> const & entityId, ComponentType const componentType, stde::any const & component) = 0;
    };

    template<typename T>
    class	ID
    {
    public:
      ID(unsigned const id) : _id(id) {}
      ID(ID<T> const & src) : _id(src._id) {}
      ID(ID<T> && src) : _id(src._id) { src._id ^= src._id; }
      ~ID(void) {}

      bool	operator<(ID<T> const & rhs) const	{ return _id < rhs._id; }
      bool	operator>(ID<T> const & rhs) const	{ return _id > rhs._id; }
      bool	operator<=(ID<T> const & rhs) const	{ return _id <= rhs._id; }
      bool	operator>=(ID<T> const & rhs) const	{ return _id >= rhs._id; }
      bool	operator!=(ID<T> const & rhs) const	{ return _id != rhs._id; }
      bool	operator==(ID<T> const & rhs) const	{ return _id == rhs._id; }

      ID<T> &	operator=(ID<T> const & src)
      {
	if (&src != this)
	  _id = src._id;
	return *this;
      }

      ID<T> &	operator=(ID<T> && src)
      {
	if (&src != this)
	  {
	    _id = src._id;
	    src._id ^= src._id;
	  }
	return *this;
      }

    private:
      unsigned	_id;
    };
  }
}

namespace	ecs = entity_component_system;
