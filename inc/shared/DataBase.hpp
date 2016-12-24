//
// DataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:30:40 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 24 14:51:49 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <array>
#include <functional>
#include <map>
#include "AssemblyBuilder.hpp"
#include "Entity.hpp"
#include "Dispatcher.hpp"
#include "IAssemblyDispatcher.hpp"
#include "IDataBase.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<typename ComponentTypes>
    class		DataBase : public IDataBase
    {
    public:
      DataBase(void) : _componentBuilders(_InitComponentUtils<ComponentTypes>::template initBuilders<0>()),
		       _componentRetrievers(_InitComponentUtils<ComponentTypes>::template initRetrievers<0>()),
		       _componentComparators(_InitComponentUtils<ComponentTypes>::template initComparators<0>()),
		       _componentSetters(_InitComponentUtils<ComponentTypes>::template initSetters<0>()),
		       _componentSettersFromRTEntity(_InitComponentUtils<ComponentTypes>::template initSettersFromRTEntity<0>()),
		       _componentInAnyIDGetters(_InitComponentUtils<ComponentTypes>::template initComponentInAnyIDGetters<0>()),
		       _entitiesNb(0), _componentsNb(0) {}

      DataBase(DataBase const &) = delete;
      DataBase(DataBase &&) = delete;
      ~DataBase(void) = default;

      DataBase &	operator=(DataBase const &) = delete;
      DataBase &	operator=(DataBase &&) = delete;

      virtual ID<ecs::Entity>	createEntity(void) { return this->createEntity("unknownEntity"); }

      virtual ID<ecs::Entity>
      createEntity(std::string const & name)
      {
	_entities.push_back({_entitiesNb, name});
	_entityComponentMap.emplace(_entitiesNb, typename decltype(_entityComponentMap)::mapped_type());
	return _entitiesNb++;
      }

      virtual void	createEntityFromAssembly(IAssembly & assembly)
      {
	Dispatcher<Assemblies, IAssemblyDispatcher, AssemblyBuilder<DataBase<ComponentTypes>>>	dsp;

	dsp.database(this);
	assembly.visit(dsp);
      }

      template<typename... ComponentsTypes, char const *... names>
      void	createEntityFromAssembly(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> & as)
      {
	as.setID(_entitiesNb);
	this->createEntity();
	_buildEntity<0, names...>(as);
      }

      virtual std::string
      getEntityName(ID<ecs::Entity> const & id) const
      {
	for (auto & pair : _entities)
	  if (pair.first == id)
	    return pair.second;
	return "";
      };

      virtual void
      setEntityName(ID<ecs::Entity> const & id, std::string const & name)
      {
	for (auto & pair : _entities)
	  if (pair.first == id)
	    pair.second = name;
      }

      virtual ID<ecs::Component>
      createComponent(ComponentTypeID const componentTypeID)
      {
	_components[static_cast<unsigned>(componentTypeID)].push_back({_componentsNb, _componentBuilders[static_cast<unsigned>(componentTypeID)](_componentsNb)});
	return _componentsNb++;
      }

      virtual ID<ecs::Component>
      createAndBindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, std::string const & componentName)
      {
	for (auto & pair : _entities)
	  if (pair.first == entityId)
	    {
	      auto	it = _entityComponentMap.find(pair.first);

	      it->second.push_back(typename decltype(_entityComponentMap)::mapped_type::value_type(componentTypeID, _componentsNb, componentName));
	      _components[static_cast<unsigned>(componentTypeID)].push_back({_componentsNb, _componentBuilders[static_cast<unsigned>(componentTypeID)](_componentsNb)});
	      return _componentsNb++;
	    }
	return 0; // THROW
      }

      virtual ID<ecs::Component>
      bindComponent(ID<ecs::Entity> const & entityId, ComponentTypeID const componentTypeID, ID<ecs::Component> const & componentId, std::string const & componentName)
      {
	for (auto & pair : _entities)
	  if (pair.first == entityId)
	    {
	      typedef typename decltype(_entityComponentMap)::mapped_type	MappedType;

	      auto	it = _entityComponentMap.find(pair.first);

	      it->second.push_back(typename MappedType::value_type(componentTypeID, componentId, componentName));
	      return componentId;
	    }
	return 0; // THROW
      }

      virtual Any
      getEntity(ID<ecs::Entity> const & id) const
      {
	auto	it = _entityComponentMap.find(id);

	if (it != _entityComponentMap.end())
	  {
	    entity::RTEntity	e(id);

	    for (auto & tup : it->second)
	      for (auto & pair : _components[static_cast<unsigned>(DataBase::_componentType(tup))])
		if (pair.first == DataBase::_componentID(tup))
		  {
		    _componentRetrievers[static_cast<unsigned>(DataBase::_componentType(tup))](e, pair.second, DataBase::_componentName(tup));
		    break;
		  }
	    return Any(e);
	  }
	return Any();
      }

      virtual Any
      getComponent(ID<ecs::Component> const & id) const
      {
	for (auto & vect : _components)
	  for (auto & pair : vect)
	    if (pair.first == id)
	      return Any(pair.second);
	return Any();
      }

      virtual Any
      getComponentFromEntity(ID<ecs::Entity> const & entityId, ID<ecs::Component> const & componentId) const
      {
	auto	it = _entityComponentMap.find(entityId);

	if (it != _entityComponentMap.end())
	  for (auto & tup : it->second)
	    if (std::get<1>(tup) == componentId)
	      for (auto & pair : _components[static_cast<unsigned>(DataBase::_componentType(tup))])
		if (pair.first == componentId)
		  return Any(pair.second);
	return Any();
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponent(std::string const & componentName) const
      {
	return _getAllEntitiesWithComponent([&componentName](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup){return std::get<2>(tup) == componentName;});
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponent(ComponentTypeID const componentTypeID) const
      {
	return _getAllEntitiesWithComponent([componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup){return DataBase::_componentType(tup) == componentTypeID;});
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponent(std::string const & componentName, ComponentTypeID const componentTypeID) const
      {
	return _getAllEntitiesWithComponent([&componentName, componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup)
					    {
					      return DataBase::_componentType(tup) == componentTypeID && DataBase::_componentName(tup) == componentName;
					    });
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponentEqualTo(ComponentTypeID const componentTypeID, Component const & value) const
      {
	return _getAllEntitiesWithComponentEqualTo(value, [componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup){return DataBase::_componentType(tup) == componentTypeID;});
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponentEqualTo(std::string const & componentName, ComponentTypeID const componentTypeID, Component const & value) const
      {
	return _getAllEntitiesWithComponentEqualTo(value,
						   [componentTypeID, &componentName](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup)
						   {
						     return DataBase::_componentType(tup) == componentTypeID && DataBase::_componentName(tup) == componentName;
						   });
      }

      virtual void
      setEntity(entity::RTEntity const & entity)
      {
	auto	entityIt = _entityComponentMap.find(entity.getID());

	if (entityIt != _entityComponentMap.end())
	  {
	    typename decltype(_entityComponentMap)::mapped_type		components(entityIt->second);

	    for (auto & componentPair : entity)
	      {
		bool	found = false;

		for (auto componentsIt = components.begin(); componentsIt != components.end(); ++componentsIt)
		  {
		    if (DataBase::_componentName(*componentsIt) == componentPair.first)
		      {
			found = true;

			for (auto & componentPairDB : _components[static_cast<unsigned>(DataBase::_componentType(*componentsIt))])
			  if (componentPairDB.first == DataBase::_componentID(*componentsIt))
			    _componentSettersFromRTEntity[static_cast<unsigned>(DataBase::_componentType(*componentsIt))](_lastChanges, entityIt->first, componentPairDB.second, componentPair);
		      }
		    if (found)
		      {
			components.erase(componentsIt);
			break;
		      }
		  }
		if (!found)
		  {
		    // create component
		  }
	      }
	  }
      }

      virtual void
      setEntities(std::vector<entity::RTEntity> const & entities)
      {
	for (auto & e : entities)
	  this->setEntity(e);
      }

      virtual void
      setComponent(ID<ecs::Entity> const & entityId, Component const & component)
      {
	auto	entityIt = _entityComponentMap.find(entityId);

	if (entityIt != _entityComponentMap.end())
	  for (auto & tup : entityIt->second)
	    if (DataBase::_componentID(tup) == component.getID())
	      for (auto & pair : _components[static_cast<unsigned>(DataBase::_componentType(tup))])
		if (pair.first == component.getID())
		  {
		    _componentSetters[static_cast<unsigned>(DataBase::_componentType(tup))](_lastChanges, entityId, pair.second, component);
		    return;
		  }
      }

      virtual std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>	getLastChanges(void) { return std::move(_lastChanges); }

      virtual std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>
      getLastChangesWithAttr(std::string const & attrName)
      {
	std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>	lastChanges;
	auto								it = _lastChanges.begin();

	while (it != _lastChanges.end())
	  {
	    ID<ecs::Component> const	id = _componentInAnyIDGetters[static_cast<unsigned>(std::get<1>(*it))](std::get<2>(*it));
	    auto			entityIt = _entityComponentMap.find(std::get<0>(*it));
	    auto const			nxtIt = std::next(it);

	    if (entityIt != _entityComponentMap.end())
	      for (auto & tup : entityIt->second)
		if (DataBase::_componentID(tup) == id)
		  for (auto & pair : _components[static_cast<unsigned>(DataBase::_componentType(tup))])
		    if (pair.first == id && pair.second.hasAttr(attrName))
		      lastChanges.splice(lastChanges.end(), _lastChanges, it);
	    it = nxtIt;
	  }
	return lastChanges;
      }

      friend std::ostream &
      operator<<(std::ostream & os, DataBase<ComponentTypes> const & db)
      {
	auto	entityIt = db._entities.begin();

	while (entityIt != db._entities.end())
	  {
	    auto	it = db._entityComponentMap.find(entityIt->first);

	    os << entityIt->second << " =>\t(" << entityIt->first << ") [with ";
	    if (it != db._entityComponentMap.end())
	      {
		auto	componentIt = it->second.begin();

		while (componentIt != it->second.end())
		  {
		    os << DataBase::_componentName(*componentIt) << ": (" << DataBase::_componentID(*componentIt) << ") ";
		    for (auto & cPair : db._components[static_cast<unsigned>(DataBase::_componentType(*componentIt))])
		      if (cPair.first == DataBase::_componentID(*componentIt))
			{
			  os << cPair.second;
			  break;
			}
		    if (++componentIt != it->second.end())
		      os << ", ";
		    else
		      break;
		  }
	      }
	    os << ']';
	    if (++entityIt != db._entities.end())
	      os << std::endl;
	    else
	      break;
	  }
	return os << std::flush;
      }

    private:
      std::vector<std::function<Component(unsigned const)>>									_componentBuilders;
      std::vector<std::function<void(entity::RTEntity &, Component const &, std::string const &)>>				_componentRetrievers;
      std::vector<std::function<bool(Component const &, Component const &)>>							_componentComparators;
      std::vector<std::function<void(std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>> &, ID<ecs::Entity> const &,
				     database::Component &, database::Component const &)>>					_componentSetters;
      std::vector<std::function<void(std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>> &, ID<ecs::Entity> const &,
				     database::Component &, entity::RTEntity::ConstIterator::value_type const &)>>		_componentSettersFromRTEntity;
      std::vector<std::function<ID<ecs::Component>(Any const &)>>								_componentInAnyIDGetters;

      std::vector<std::pair<ID<ecs::Entity>, std::string>>										_entities;
      std::map<ID<ecs::Entity>, std::vector<std::tuple<ComponentTypeID, ID<ecs::Component>, std::string>>>				_entityComponentMap;
      std::array<std::vector<std::pair<ID<ecs::Component>, Component>>, static_cast<unsigned>(ComponentTypeID::ComponentTypesNb)>	_components;
      unsigned																_entitiesNb;
      unsigned																_componentsNb;

      std::list<std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>>	_lastChanges;

    private:
      template<unsigned idx, char const * _name, char const *... _names, typename... ComponentsTypes, char const *... names>
      void
      _buildEntity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> & as, typename std::enable_if<idx < sizeof...(names)>::type * = nullptr)
      {
	typedef typename decltype(_entityComponentMap)::mapped_type	MappedType;

	constexpr ComponentTypeID	componentTypeID = ComponentTypes::template GetComponentTypeID<decltype(as.template getComponent<_name>())>::typeID;

	as.template getComponent<_name>().setID(_componentsNb);
	_entityComponentMap.at(as.getID()).push_back(typename MappedType::value_type(componentTypeID, _componentsNb, std::get<idx>(std::tuple<decltype(std::string(names))...>(names...))));
	_components[static_cast<unsigned>(componentTypeID)].push_back({_componentsNb++, as.template getComponent<_name>()});
	_buildEntity<idx + 1, _names...>(as);
      }

      template<unsigned idx, typename... ComponentsTypes, char const *... names>
      void	_buildEntity(entity::CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &, typename std::enable_if<idx == sizeof...(names)>::type * = nullptr) {}

      virtual std::list<entity::RTEntity>
      _getAllEntitiesWithComponent(std::function<bool(std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const &)> const & cond) const
      {
	std::list<entity::RTEntity>	entities;

	for (auto & ePair : _entityComponentMap)
	  for (auto & tup0 : ePair.second)
	    if (cond(tup0))
	      {
		entity::RTEntity	e(ePair.first);

		for (auto & tup1 : ePair.second)
		  for (auto & cPair : _components[static_cast<unsigned>(DataBase::_componentType(tup1))])
		    if (cPair.first == std::get<1>(tup1))
		      {
			_componentRetrievers[static_cast<unsigned>(DataBase::_componentType(tup1))](e, cPair.second, DataBase::_componentName(tup1));
			break;
		      }
		entities.push_back(e);
		break;
	      }
	return entities;
      }

      virtual std::list<entity::RTEntity>
      _getAllEntitiesWithComponentEqualTo(Component const & value, std::function<bool(std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const &)> const & cond) const
      {
	std::list<entity::RTEntity>	entities;
	bool				found;

	for (auto & ePair : _entityComponentMap)
	  {
	    found = false;
	    for (auto & tup0 : ePair.second)
	      {
		if (cond(tup0))
		  {
		    for (auto & cPair0 : _components[static_cast<unsigned>(DataBase::_componentType(tup0))])
		      if (cPair0.first == DataBase::_componentID(tup0) && _componentComparators[static_cast<unsigned>(DataBase::_componentType(tup0))](value, cPair0.second))
			{
			  entity::RTEntity	e(ePair.first);

			  for (auto & tup1 : ePair.second)
			    for (auto & cPair1 : _components[static_cast<unsigned>(DataBase::_componentType(tup1))])
			      if (cPair1.first == std::get<1>(tup1))
				{
				  _componentRetrievers[static_cast<unsigned>(DataBase::_componentType(tup1))](e, cPair1.second, DataBase::_componentName(tup1));
				  break;
				}
			  entities.push_back(e);
			  found = true;
			  break;
			}
		  }
		if (found)
		  break;
	      }
	  }
	return entities;
      }

      static ComponentTypeID		_componentType(typename decltype(_entityComponentMap)::mapped_type::value_type const & tup)	{ return std::get<0>(tup); }
      static ID<ecs::Component> const &	_componentID(typename decltype(_entityComponentMap)::mapped_type::value_type const & tup)	{ return std::get<1>(tup); }
      static std::string const &	_componentName(typename decltype(_entityComponentMap)::mapped_type::value_type const & tup)	{ return std::get<2>(tup); }

    private:
      template<typename>
      struct	_InitComponentUtils;

      template<ComponentTypeID... componentTypesIDs, typename... Components>
      struct	_InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>
      {
	template<unsigned idx, typename... ComponentBuilders>
	static decltype(_componentBuilders)
	initBuilders(ComponentBuilders&&... componentBuilders, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initBuilders<idx + 1, ComponentBuilders..., typename decltype(_componentBuilders)::value_type>(std::forward<ComponentBuilders>(componentBuilders)...,
													    [](unsigned const componentsNb){return typename CTPair::Type(componentsNb);});
	}

	template<unsigned idx, typename... ComponentBuilders>
	static decltype(_componentBuilders)
	initBuilders(ComponentBuilders&&... componentBuilders, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentBuilders>(componentBuilders)... };
	}

	template<unsigned idx, typename... ComponentRetrievers>
	static decltype(_componentRetrievers)
	initRetrievers(ComponentRetrievers&&... componentRetrievers, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initRetrievers<idx + 1, ComponentRetrievers..., typename decltype(_componentRetrievers)::value_type>
	    (std::forward<ComponentRetrievers>(componentRetrievers)...,
	     [](entity::RTEntity & e, Component const & c, std::string const & name){e.addComponent(name, typename CTPair::Type(c));});
	}

	template<unsigned idx, typename... ComponentRetrievers>
	static decltype(_componentRetrievers)
	initRetrievers(ComponentRetrievers&&... componentRetrievers, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentRetrievers>(componentRetrievers)... };
	}

	template<unsigned idx, typename... ComponentComparators>
	static decltype(_componentComparators)
	initComparators(ComponentComparators&&... componentComparators, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initComparators<idx + 1, ComponentComparators..., typename decltype(_componentComparators)::value_type>
	    (std::forward<ComponentComparators>(componentComparators)...,
	     [](Component const & lhs, Component const & rhs){return typename CTPair::Type(lhs) == typename CTPair::Type(rhs);});
	}

	template<unsigned idx, typename... ComponentComparators>
	static decltype(_componentComparators)
	initComparators(ComponentComparators&&... componentComparators, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentComparators>(componentComparators)... };
	}

	template<unsigned idx, typename... ComponentSetters>
	static decltype(_componentSetters)
	initSetters(ComponentSetters&&... componentSetters, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  constexpr ComponentTypeID	typeID = CTPair::typeID;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initSetters<idx + 1, ComponentSetters..., typename decltype(_componentSetters)::value_type>
	    (std::forward<ComponentSetters>(componentSetters)..., [typeID](decltype(DataBase::_lastChanges) & lastChanges, ID<ecs::Entity> const & eID,
									   database::Component & oldComponent, database::Component const & newComponent)
	     {
	       typename CTPair::Type const	newCTComponent = newComponent;

	       if (typename CTPair::Type(oldComponent) != newCTComponent)
		 {
		   lastChanges.push_back(std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>(eID, typeID, newCTComponent));
		   oldComponent = std::move(newCTComponent);
		 }
	     });
	}

	template<unsigned idx, typename... ComponentSetters>
	static decltype(_componentSetters)
	initSetters(ComponentSetters&&... componentSetters, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentSetters>(componentSetters)... };
	}

	template<unsigned idx, typename... ComponentSetters>
	static decltype(_componentSettersFromRTEntity)
	initSettersFromRTEntity(ComponentSetters&&... componentSetters, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  constexpr ComponentTypeID	typeID = CTPair::typeID;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initSettersFromRTEntity<idx + 1, ComponentSetters..., typename decltype(_componentSettersFromRTEntity)::value_type>
	    (std::forward<ComponentSetters>(componentSetters)..., [typeID](decltype(DataBase::_lastChanges) & lastChanges, ID<ecs::Entity> const & eID,
									   database::Component & oldComponent, entity::RTEntity::ConstIterator::value_type const & newComponentPair)
	     {
	       typename CTPair::Type const	newComponent = newComponentPair.second->component<typename CTPair::Type>(newComponentPair.first);

	       if (typename CTPair::Type(oldComponent) != newComponent)
		 {
		   lastChanges.push_back(std::tuple<ID<ecs::Entity>, ComponentTypeID, Any>(eID, typeID, newComponent));
		   oldComponent = std::move(newComponent);
		 }
	     });
	}

	template<unsigned idx, typename... ComponentSetters>
	static decltype(_componentSettersFromRTEntity)
	initSettersFromRTEntity(ComponentSetters&&... componentSetters, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentSetters>(componentSetters)... };
	}

	template<unsigned idx, typename... Lambda>
	static decltype(_componentInAnyIDGetters)
	initComponentInAnyIDGetters(Lambda&&... lambdas, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentUtils<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    initComponentInAnyIDGetters<idx + 1, Lambda..., typename decltype(_componentInAnyIDGetters)::value_type>
	    (std::forward<Lambda>(lambdas)...,
	     [](Any const & component){ return component.getValue<typename CTPair::Type>().getID(); });
	}

	template<unsigned idx, typename... Lambda>
	static decltype(_componentInAnyIDGetters)
	initComponentInAnyIDGetters(Lambda&&... lambdas, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<Lambda>(lambdas)... };
	}
      };
    };
  }
}
