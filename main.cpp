//
// main.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 16:14:24 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 19 00:19:50 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cxxabi.h>
#include <iostream>
#include <memory>
#include "DataBase.hpp"

typedef typename std::underlying_type<ecs::database::ComponentTypeID>::type	lel_t;

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

  asPhysicObj.getComponent<::pos>().getAttr<::x>() = 50;
  asPhysicObj.getComponent<::pos>().getAttr<::y>() = 50;
  asPhysicObj.getComponent<::size>().getAttr<::x>() = 25;
  asPhysicObj.getComponent<::size>().getAttr<::y>() = 25;
  asPhysicObj.getComponent<::dir>().getAttr<::x>() = 75;
  asPhysicObj.getComponent<::dir>().getAttr<::y>() = 75;
  asPlayer.getComponent<::physicObjID>().setAttr<::value>(asPhysicObj.getID());
  asPlayer.getComponent<::health>().setAttr<::value>(100);

  std::cout << "physicObj =>\t" << asPhysicObj << std::endl;
  std::cout << "player =>\t" << asPlayer << std::endl;

  std::cout << "-----DATABASE-----" << std::endl;
  std::cout << dynamic_cast<ecs::database::DataBase<RTypeComponents> &>(*db) << std::endl;
  std::cout << "------------------" << std::endl;

  asPhysicObj = db->getEntity(asPhysicObj.getID()).getValue<ecs::entity::RTEntity>();
  asPlayer = db->getEntity(asPlayer.getID()).getValue<ecs::entity::RTEntity>();

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
    std::cout << "someEntity =>\t" << e << std::endl;
  std::cout << "------------------" << std::endl;

  entityList = db->getAllEntitiesWithComponentEqualTo(::health, ecs::database::ComponentTypeID::BasicUnsignedShort,
						      db->getEntity(asPlayer.getID()).getValue<ecs::entity::RTEntity>().getComponent<ecs::component::Basic<unsigned short>>(::health));
  for (auto & e : entityList)
    std::cout << "someEntity =>\t" << e << std::endl;
  std::cout << "------------------" << std::endl;

  return 0;
}
