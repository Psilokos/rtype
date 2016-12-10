//
// test.cpp for  in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Nov 29 11:48:30 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 00:48:13 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cstring>
#include <experimental/string_view>
#include <iostream>
#include <cstdint>
#include "DataBaseEntity.hpp"
#include "Entity.hpp"

constexpr char	pos[] = "pos";
constexpr char	size[] = "size";

constexpr char	x[] = "x";
constexpr char	y[] = "y";
constexpr char	ttl[] = "TTL";

namespace	entity_component_system::component
{
  typedef Component<ct::TypesWrapper<std::uint16_t, std::uint16_t>, ::x, ::y>	Vector2;
}

namespace	entity_component_system::entity
{
  typedef Entity<ct::TypesWrapper<ecs::component::Vector2, ecs::component::Vector2>, ::pos, ::size>		Player;
}

void	test(void)
{
  {
    std::string			testS0("qweqwe");
    std::string			testS1(testS0);
    ecs::database::Entity	test("testEntity", {ecs::database::Component(std::forward_as_tuple(testS0), "test"), ecs::database::Component(std::tuple<std::string>(testS1), "test")}, "moved", "copied");

    std::cout << "testS0 => " << testS0 << std::endl;
    std::cout << "testS1 => " << testS1 << std::endl;
    std::cout << test << std::endl;
  }
  {
    ecs::database::Component	size(std::forward_as_tuple<std::uint16_t, std::uint16_t>(100, 75), "x", "y");
    ecs::database::Component	pos(std::forward_as_tuple<std::uint16_t, std::uint16_t, std::uint8_t>(size.getAttr<std::uint16_t>("x") / 3, size.getAttr<std::uint16_t>("y") / 2, 10), "x", "y", "TTL");
    ecs::database::Entity	player("player#23", {pos, size}, "pos", "size");
    unsigned			playerTTL = 48;

    std::cout << player << std::endl;

    pos = player.delComponent("pos");
    player.setComponent("pos", pos);

    std::cout << player << std::endl;

    player["pos"].setAttr<unsigned char>("TTL", std::move(playerTTL));

    if (player["pos"].hasAttr("TTL"))
      std::cout << player << std::endl;

    {
      ecs::component::Component<ct::TypesWrapper<std::uint16_t, std::uint16_t, std::uint8_t>, ::x, ::y, ::ttl>	c0(pos);
      std::string												s = "qweqwe";
      ecs::component::Component<ct::TypesWrapper<std::string>, ::x>						c1(std::move(s));
      ecs::component::Component<ct::TypesWrapper<std::uint16_t, std::uint8_t>, ::x, ::ttl>			c2(pos);

      std::cout << "c0: " << c0 << std::endl;
      c0.setAttr<::x>(0);
      c0.setAttr<::y>(1);
      c0.setAttr<::ttl>(0x21);
      std::cout << "c0: " << c0 << std::endl;

      std::cout << "c1: " << c1 << std::endl;
      std::cout << std::boolalpha << "is 's' empty => " << s.empty() << std::noboolalpha << std::endl;

      std::cout << "c2: " << c2 << std::endl;
      {
	ecs::component::Vector2 const	pos(23, 42);
	ecs::component::Vector2	const	size(32, 24);
	ecs::entity::Player const	p[] =
	  {
	    ecs::entity::Player(pos, size),
	    ecs::entity::Player(ecs::component::Vector2(0, 0), size),
	    ecs::entity::Player(pos, ecs::component::Vector2(0, 0)),
	    ecs::entity::Player(ecs::component::Vector2(0, 0), ecs::component::Vector2(0, 0)),
	  };
	ecs::entity::Player		mutablePlayer = player;

	for (unsigned i = 0; i < sizeof(p) / sizeof(ecs::entity::Player); ++i)
	  std::cout << "player#" << std::to_string(i) << " => " << p[i] << std::endl;
	std::cout << "mutablePlayer.pos.x = " << mutablePlayer.getComponent<::pos>().getAttr<::x>() << std::endl;
	mutablePlayer.setComponent<::pos>(pos);
	std::cout << "mutablePlayer.pos.x = " << mutablePlayer.getComponent<::pos>().getAttr<::x>() << std::endl;
	for (unsigned i = 0; i < sizeof(p) / sizeof(ecs::entity::Player); ++i)
	  std::cout << "player#" << std::to_string(i) << " => " << p[i] << std::endl;
	mutablePlayer.getComponent<::pos>() = player[::pos];
	std::cout << "mutablePlayer => " << mutablePlayer << std::endl;
	player[::size] = size;
	std::cout << player << std::endl;
	// player = mutablePlayer; =========> NEXT STEP
      }
    }
  }
}

int	main(void)
{
  test();
  return 0;
}
