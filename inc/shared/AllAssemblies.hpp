//
// AllAssemblies.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Dec 19 02:53:26 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 29 17:59:45 2016 Gabriel CADET
//

#pragma once

#include "AllComponents.hpp"
#include "ID.hpp"

// les elements marquer par 'uc' sont utiliser dans ce use case

// pour eviter les cross includes
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

// differents noms de components
constexpr char	pos[] = "pos";
constexpr char	dir[] = "dir";

constexpr char	physicObjID[] = "physicObjID";
constexpr char	health[] = "health";

constexpr char	test0[] = "test0";
constexpr char	test1[] = "test1";

constexpr char	key[] = "key"; // uc
constexpr char	count[] = "count"; // uc
constexpr char	result[] = "result"; // uc

constexpr char	RoomInfo[] = "RoomInfo";
constexpr char	ConInfo[] = "ConInfo";
constexpr char	UserInfo[] = "UserInfo";

// definitions de types d'entity
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

    typedef CTEntity<ct::TypesWrapper<component::DynAllocBuffer<std::uint8_t>, component::Buffer<std::uint8_t>, component::DynAllocBuffer<std::uint8_t>>, ::key, ::count, ::result>	HMAC; // uc
    typedef CTEntity<ct::TypesWrapper<component::Basic<std::uint32_t>>, ::result>													TOTP; // uc

    typedef CTEntity<ct::TypesWrapper<component::RoomInfo>, ::RoomInfo> Room;

    typedef CTEntity<ct::TypesWrapper<component::UserInfo, component::ConInfo>, ::UserInfo, ::ConInfo> User;
  }

  namespace	database
  {
    typedef ct::TypesWrapper<entity::PhysicObject, entity::Player, entity::Test<std::string>, entity::HMAC, entity::TOTP, entity::Room, entity::User>		Assemblies; // uc
  }
}
