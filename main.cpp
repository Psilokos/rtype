//
// main.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 16:14:24 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 22 20:40:50 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cxxabi.h>
#include <iostream>
#include <memory>
#include "DataBase.hpp"

typedef typename std::underlying_type<ecs::database::ComponentTypeID>::type	lel_t;

static inline void	dumpDB(std::unique_ptr<ecs::database::IDataBase> const & db)
{
  std::cout << "-----DATABASE-----" << std::endl;
  std::cout << dynamic_cast<ecs::database::DataBase<RTypeComponents> &>(*db) << std::endl;
  std::cout << "------------------" << std::endl << std::endl;
}

int	main(int, char *[])
{
  std::unique_ptr<ecs::database::IDataBase>	db(new ecs::database::DataBase<RTypeComponents>());
  ecs::entity::PhysicObject			asPhysicObj;
  ecs::entity::Player				asPlayer;
  std::list<ecs::entity::RTEntity>		entityList;

  db->bindComponent(db->createEntity("qweqwe"), ecs::database::ComponentTypeID::BasicUnsignedShort, db->createComponent(ecs::database::ComponentTypeID::BasicUnsignedShort), "azeaze");
  db->createEntityFromAssembly(asPhysicObj);
  db->createEntityFromAssembly(asPlayer);
  db->setEntityName(asPhysicObj.getID(), "physicObj");
  db->setEntityName(asPlayer.getID(), "player");

  dumpDB(db);

  asPhysicObj = db->getEntity(asPhysicObj.getID()).getValue<ecs::entity::RTEntity>();
  asPlayer = db->getEntity(asPlayer.getID()).getValue<ecs::entity::RTEntity>();

  asPhysicObj.getComponent<::pos>().getAttr<::x>() = 50;
  asPhysicObj.getComponent<::pos>().getAttr<::y>() = 50;
  asPhysicObj.getComponent<::size>().getAttr<::x>() = 25;
  asPhysicObj.getComponent<::size>().getAttr<::y>() = 25;
  asPhysicObj.getComponent<::dir>().getAttr<::x>() = 75;
  asPhysicObj.getComponent<::dir>().getAttr<::y>() = 75;
  asPlayer.getComponent<::physicObjID>().setAttr<::value>(asPhysicObj.getID());
  asPlayer.getComponent<::health>().setAttr<::value>(100);

  db->setComponent(asPlayer.getID(), asPlayer.getComponent<::physicObjID>());

  dumpDB(db);

  db->setEntities({asPhysicObj, asPlayer});

  std::cout << "physicObj =>\t" << asPhysicObj << std::endl;
  std::cout << "player =>\t" << asPlayer << std::endl << std::endl;

  dumpDB(db);

  std::cout << "physicObj =>\t" << asPhysicObj << std::endl;
  std::cout << "player =>\t" << asPlayer << std::endl;
  std::cout << "------------------" << std::endl;

  entityList = db->getAllEntitiesWithComponent(::pos);
  for (auto & e : entityList)
    std::cout << "physicObj =>\t" << e << std::endl;
  std::cout << "------------------" << std::endl;

  entityList = db->getAllEntitiesWithComponent(::dir, ecs::database::ComponentTypeID::Vector2Int);
  for (auto & e : entityList)
    std::cout << "physicObj =>\t" << e << std::endl;
  std::cout << "------------------" << std::endl;

  entityList = db->getAllEntitiesWithComponentEqualTo(ecs::database::ComponentTypeID::BasicUnsignedShort,
						      db->getEntity(asPlayer.getID()).getValue<ecs::entity::RTEntity>().getComponent<ecs::component::Basic<unsigned short>>(::health));
  for (auto & e : entityList)
    {
      std::cout << "someEntity =>\t(" << e.getID() << ") [with ";
      for (auto & componentPair : e)
	std::cout << componentPair.first << ": " << *componentPair.second << ", ";
      std::cout << ']' << std::endl;
    }
  std::cout << "------------------" << std::endl;

  entityList = db->getAllEntitiesWithComponentEqualTo(::health, ecs::database::ComponentTypeID::BasicUnsignedShort,
						      db->getEntity(asPlayer.getID()).getValue<ecs::entity::RTEntity>().getComponent<ecs::component::Basic<unsigned short>>(::health));
  for (auto & e : entityList)
    {
      auto it = e.begin();

      std::cout << "someEntity =>\t(" << e.getID() << ") [with ";
      while (it != e.end())
	{
	  std::cout << it->first << ": " << *it->second;
	  if (++it != e.end())
	    std::cout << ", ";
	  else
	    break;
	}
      std::cout << ']' << std::endl;
    }
  std::cout << "------------------" << std::endl;

  return 0;
}
