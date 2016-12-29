//
// AllComponents.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 19:35:32 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 29 17:48:45 2016 Gabriel CADET
//

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include "Component.hpp"
#include "ComponentTypes.hpp"
#include "ID.hpp"

// les elements marquer par 'uc' sont utiliser dans ce use case

// differents noms d'attributs
constexpr char	test[] = "test";

constexpr char	value[] = "value"; // uc

constexpr char	x[] = "x";
constexpr char	y[] = "y";

constexpr char	data[] = "data"; // uc
constexpr char	size[] = "size"; // uc

/* RoomInfo component attr */
constexpr char	slots[] = "slots";
constexpr char	clients[] = "clients";
constexpr char	spectate[] = "spectate";
constexpr char	gamestate[] = "gamestate";

/* ConInfo component addt */
constexpr char	ip[] = "ip";
constexpr char	port[] = "port";

// definitions de types de components
namespace	entity_component_system
{
  namespace	component
  {
    template<typename T>
    using Basic = Component<ct::TypesWrapper<T>, ::value>; // uc

    template<typename T>
    using Vector2 = Component<ct::TypesWrapper<T, T>, ::x, ::y>;

    template<typename T>
    using Test = Component<ct::TypesWrapper<T>, ::test>;

    template<typename T>
    using Buffer = Component<ct::TypesWrapper<typename std::decay<T>::type *, std::uint32_t>, ::data, ::size>; // uc

    template<typename T>
    using DynAllocBuffer = Component<ct::TypesWrapper<std::shared_ptr<typename std::decay<T>::type>, std::uint32_t>, ::data, ::size>; // uc

    typedef ecs::component::Component<ct::TypesWrapper<char, char, bool, int>, ::slots, ::clients, ::spectate, ::gamestate> RoomInfo;

    typedef ecs::component::Component<ct::TypesWrapper<std::string, std::string>, ::ip, ::port> ConInfo;
    typedef ecs::component::Basic<std::string>	UserInfo;
  }
}

// le fameux type a passer a la DB a l'instanciation de son type lors de sa definition: 'DataBase<RTypeComponents> db;'
typedef ecs::database::ComponentTypes<ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BasicIdEntity,		ecs::component::Basic<ecs::ID<ecs::Entity>>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BasicUnsignedShort,	ecs::component::Basic<unsigned short>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BasicUInt32,		ecs::component::Basic<std::uint32_t>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::Vector2Int,		ecs::component::Vector2<int>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::Vector2Unsigned,		ecs::component::Vector2<unsigned>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::TestUnsigned,		ecs::component::Test<unsigned>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::TestString,		ecs::component::Test<std::string>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BufferUInt8,		ecs::component::Buffer<std::uint8_t>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::RoomInfo,		ecs::component::RoomInfo>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::ConInfo,			ecs::component::ConInfo>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::UserInfo,		ecs::component::UserInfo>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::DynAllocBufferUInt8,	ecs::component::DynAllocBuffer<std::uint8_t>>>		RTypeComponents; // uc
