//
// IAssemblyDispatcher.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec 16 18:46:43 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 21:10:35 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <cstdint>
#include "AllComponents.hpp"
#include "CTEntity.hpp"
#include "ID.hpp"
#include "IDispatcher.hpp"

constexpr char	pos[] = "pos";
constexpr char	size[] = "size";
constexpr char	dir[] = "dir";

constexpr char	physicObjID[] = "physicObjID";
constexpr char	health[] = "health";

namespace	entity_component_system
{
  namespace	entity
  {
    typedef CTEntity<ct::TypesWrapper<component::Vector2<unsigned>, component::Vector2<unsigned>, component::Vector2<int>>, ::pos, ::size, ::dir>	PhysicObject;
    typedef CTEntity<ct::TypesWrapper<component::Basic<ID<Entity>>, component::Basic<std::uint16_t>>, ::physicObjID, ::health>				Player;
  }

  namespace	database
  {
    typedef ct::TypesWrapper<entity::PhysicObject, entity::Player>		Assemblies;

    class	IAssemblyDispatcher : public IDispatcher<Assemblies> {};
  }
}

namespace	ecs = entity_component_system;
