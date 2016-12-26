//
// AllAssemblies.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Dec 19 02:53:26 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 22 21:48:42 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "AllComponents.hpp"
#include "ID.hpp"

namespace	entity_component_system
{
  namespace	entity
  {
    template<typename, char const *...>
    class	CTEntity;

    class	CTEntity<ct::TypesWrapper<>>;

    template<typename... ComponentsTypes, char const *... names>
    class	CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>;
  }
}

constexpr char	pos[] = "pos";
constexpr char	size[] = "size";
constexpr char	dir[] = "dir";

constexpr char	physicObjID[] = "physicObjID";
constexpr char	health[] = "health";

constexpr char	test0[] = "test0";
constexpr char	test1[] = "test1";

namespace	entity_component_system
{
  namespace	entity
  {
    typedef CTEntity<ct::TypesWrapper<component::Vector2<unsigned>, component::Vector2<unsigned>, component::Vector2<int>>, ::pos, ::size, ::dir>	PhysicObject;
    typedef CTEntity<ct::TypesWrapper<component::Basic<ID<ecs::Entity>>, component::Basic<std::uint16_t>>, ::physicObjID, ::health>			Player;

    template<typename T>
    using Test = CTEntity<ct::TypesWrapper<ecs::component::Test<T>>, ::test>;

    template<typename T>
    using Test2 = CTEntity<ct::TypesWrapper<ecs::component::Test<T>, ecs::component::Test<T>>, ::test0, ::test1>;
  }

  namespace	database
  {
    typedef ct::TypesWrapper<entity::PhysicObject, entity::Player, entity::Test<std::string>>		Assemblies;
  }
}
