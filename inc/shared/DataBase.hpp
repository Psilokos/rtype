//
// DataBase.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Nov 28 15:30:40 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 19 02:40:07 2016 Victorien LE COUVIOUR--TUFFET
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
      DataBase(void) : _componentBuilders(_InitComponentBuilders<ComponentTypes>::template init<0>()),
		       _componentRetrievers(_InitComponentRetrievers<ComponentTypes>::template init<0>()),
		       _componentComparators(_InitComponentComparators<ComponentTypes>::template init<0>()) {}

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
	      typedef typename decltype(_entityComponentMap)::mapped_type	MappedType;

	      auto	it = _entityComponentMap.find(pair.first);

	      it->second.push_back(typename MappedType::value_type(componentTypeID, _componentsNb, componentName));
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
	      return _componentsNb++;
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
	      for (auto & pair : _components[static_cast<unsigned>(std::get<0>(tup))])
		if (pair.first == std::get<1>(tup))
		  {
		    _componentRetrievers[static_cast<unsigned>(std::get<0>(tup))](e, pair.second, std::get<2>(tup));
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
	      for (auto & pair : _components[static_cast<unsigned>(std::get<0>(tup))])
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
	return _getAllEntitiesWithComponent([componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup){return std::get<0>(tup) == componentTypeID;});
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponent(std::string const & componentName, ComponentTypeID const componentTypeID) const
      {
	return _getAllEntitiesWithComponent([&componentName, componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup)
					    {
					      return std::get<0>(tup) == componentTypeID && std::get<2>(tup) == componentName;
					    });
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponentEqualTo(ComponentTypeID const componentTypeID, Component const & value) const
      {
	return _getAllEntitiesWithComponentEqualTo(value, [componentTypeID](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup){return std::get<0>(tup) == componentTypeID;});
      }

      virtual std::list<entity::RTEntity>
      getAllEntitiesWithComponentEqualTo(std::string const & componentName, ComponentTypeID const componentTypeID, Component const & value) const
      {
	return _getAllEntitiesWithComponentEqualTo(value,
						   [componentTypeID, &componentName](std::tuple<ComponentTypeID, ID<ecs::Component>, std::string> const & tup)
						   {
						     return std::get<0>(tup) == componentTypeID && std::get<2>(tup) == componentName;
						   });
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
		    os << std::get<2>(*componentIt) << ": (" << std::get<1>(*componentIt) << ") ";
		    for (auto & cPair : db._components[static_cast<unsigned>(std::get<0>(*componentIt))])
		      if (cPair.first == std::get<1>(*componentIt))
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
      std::vector<std::function<Component(unsigned const)>>										_componentBuilders;
      std::vector<std::function<void(entity::RTEntity &, Component const &, std::string const &)>>					_componentRetrievers;
      std::vector<std::function<bool(Component const &, Component const &)>>								_componentComparators;

      std::vector<std::pair<ID<ecs::Entity>, std::string>>										_entities;
      std::map<ID<ecs::Entity>, std::vector<std::tuple<ComponentTypeID, ID<ecs::Component>, std::string>>>				_entityComponentMap;
      std::array<std::vector<std::pair<ID<ecs::Component>, Component>>, static_cast<unsigned>(ComponentTypeID::ComponentTypesNb)>	_components;
      unsigned																_entitiesNb;
      unsigned																_componentsNb;

    private:
      template<typename>
      struct	_InitComponentBuilders;

      template<ComponentTypeID... componentTypesIDs, typename... Components>
      struct	_InitComponentBuilders<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>
      {
	template<unsigned idx, typename... ComponentBuilders>
	static std::vector<std::function<database::Component(unsigned const)>>
	init(ComponentBuilders&&... componentBuilders, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentBuilders<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    init<idx + 1, ComponentBuilders..., std::function<database::Component(unsigned const)>>(std::forward<ComponentBuilders>(componentBuilders)...,
												    [](unsigned const componentsNb){return typename CTPair::Type(componentsNb);});
	}

	template<unsigned idx, typename... ComponentBuilders>
	static std::vector<std::function<database::Component(unsigned const)>>
	init(ComponentBuilders&&... componentBuilders, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentBuilders>(componentBuilders)... };
	}
      };

      template<typename>
      struct	_InitComponentRetrievers;

      template<ComponentTypeID... componentTypesIDs, typename... Components>
      struct	_InitComponentRetrievers<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>
      {
	template<unsigned idx, typename... ComponentRetrievers>
	static std::vector<std::function<void(entity::RTEntity &, Component const &, std::string const &)>>
	init(ComponentRetrievers&&... componentRetrievers, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentRetrievers<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    init<idx + 1, ComponentRetrievers..., std::function<void(entity::RTEntity &, Component const &, std::string const &)>>
	    (std::forward<ComponentRetrievers>(componentRetrievers)...,
	     [](entity::RTEntity & e, Component const & c, std::string const & name){e.addComponent(name, typename CTPair::Type(c));});
	}

	template<unsigned idx, typename... ComponentRetrievers>
	static std::vector<std::function<void(entity::RTEntity &, Component const &, std::string const &)>>
	init(ComponentRetrievers&&... componentRetrievers, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentRetrievers>(componentRetrievers)... };
	}
      };

      template<typename>
      struct	_InitComponentComparators;

      template<ComponentTypeID... componentTypesIDs, typename... Components>
      struct	_InitComponentComparators<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>
      {
	template<unsigned idx, typename... ComponentComparators>
	static std::vector<std::function<bool(Component const &, Component const &)>>
	init(ComponentComparators&&... componentComparators, typename std::enable_if<idx < sizeof...(Components)>::type * = nullptr)
	{
	  typedef typename ComponentTypes::template GetComponentTypePair<idx>::Type	CTPair;

	  return _InitComponentComparators<database::ComponentTypes<ComponentTypePair<componentTypesIDs, Components>...>>::template
	    init<idx + 1, ComponentComparators..., std::function<bool(Component const &, Component const &)>>
	    (std::forward<ComponentComparators>(componentComparators)...,
	     [](Component const & lhs, Component const & rhs){return typename CTPair::Type(lhs) == typename CTPair::Type(rhs);});
	}

	template<unsigned idx, typename... ComponentComparators>
	static std::vector<std::function<bool(Component const &, Component const &)>>
	init(ComponentComparators&&... componentComparators, typename std::enable_if<idx == sizeof...(Components)>::type * = nullptr)
	{
	  return { std::forward<ComponentComparators>(componentComparators)... };
	}
      };

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
		  for (auto & cPair : _components[static_cast<unsigned>(std::get<0>(tup1))])
		    if (cPair.first == std::get<1>(tup1))
		      {
			_componentRetrievers[static_cast<unsigned>(std::get<0>(tup1))](e, cPair.second, std::get<2>(tup1));
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
		    for (auto & cPair0 : _components[static_cast<unsigned>(std::get<0>(tup0))])
		      if (cPair0.first == std::get<1>(tup0) && _componentComparators[static_cast<unsigned>(std::get<0>(tup0))](value, cPair0.second))
			{
			  entity::RTEntity	e(ePair.first);

			  for (auto & tup1 : ePair.second)
			    for (auto & cPair1 : _components[static_cast<unsigned>(std::get<0>(tup1))])
			      if (cPair1.first == std::get<1>(tup1))
				{
				  _componentRetrievers[static_cast<unsigned>(std::get<0>(tup1))](e, cPair1.second, std::get<2>(tup1));
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
    };
  }
}
