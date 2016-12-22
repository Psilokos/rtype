//
// AllComponents.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 19:35:32 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 21 21:21:20 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"
#include "ComponentTypes.hpp"
#include "ID.hpp"

constexpr char	test[] = "test";

constexpr char	value[] = "value";

constexpr char	x[] = "x";
constexpr char	y[] = "y";

namespace	entity_component_system
{
  namespace	component
  {
    template<typename T>
    using Basic = Component<ct::TypesWrapper<T>, ::value>;

    template<typename T>
    using Vector2 = Component<ct::TypesWrapper<T, T>, ::x, ::y>;

    template<typename T>
    using Test = Component<ct::TypesWrapper<T>, ::test>;
  }
}

typedef ecs::database::ComponentTypes<ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BasicIdEntity,		ecs::component::Basic<ecs::ID<ecs::Entity>>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::BasicUnsignedShort,	ecs::component::Basic<unsigned short>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::Vector2Int,		ecs::component::Vector2<int>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::Vector2Unsigned,		ecs::component::Vector2<unsigned>>,
				      ecs::database::ComponentTypePair<ecs::database::ComponentTypeID::TestString,		ecs::component::Test<std::string>>>		RTypeComponents;
