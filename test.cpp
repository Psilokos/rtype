//
// test.cpp for  in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Nov 29 11:48:30 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec 13 15:46:56 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cstdint>
#include <iostream>
#include "Entity.hpp"

constexpr char	pos[] = "pos";
constexpr char	size[] = "size";

constexpr char	x[] = "x";
constexpr char	y[] = "y";
constexpr char	ttl[] = "TTL";

constexpr char	moveTest[] = "moveTest";

namespace	entity_component_system::component
{
  typedef Component<ct::TypesWrapper<std::uint16_t, std::uint16_t>, ::x, ::y>	Vector2;
  typedef Component<ct::TypesWrapper<std::string>, ::moveTest>			MoveTest;
}

namespace	entity_component_system::entity
{
  typedef CTEntity<ct::TypesWrapper<ecs::component::Vector2, ecs::component::Vector2>, ::pos, ::size>	Player;
  typedef CTEntity<ct::TypesWrapper<ecs::component::MoveTest>, ::moveTest>				MoveTest;
}

void	test(void)
{
  {
    std::string			testS0("qweqwe");
    std::string			testS1(testS0);
    ecs::database::Entity	test({{std::hash<std::string>{}("moved"), ecs::database::Component(std::forward_as_tuple(testS0), "testS0")},
	  {std::hash<std::string>{}("copied"), ecs::database::Component(std::tuple<std::string>(testS1), "testS1")}});

    std::cout << "testS0 => " << testS0 << std::endl;
    std::cout << "testS1 => " << testS1 << std::endl;
    std::cout << "testEntity => " << test << std::endl;
    std::cout << std::endl;
  }
  {
    ecs::database::Component	size(std::forward_as_tuple<std::uint16_t, std::uint16_t>(100, 75), "x", "y");
    ecs::database::Component	pos(std::forward_as_tuple<std::uint16_t, std::uint16_t, std::uint16_t>(size.getAttr<std::uint16_t>("x") / 3, size.getAttr<std::uint16_t>("y") / 2, 10), "x", "y", "TTL");
    ecs::database::Entity	player({{std::hash<std::string>{}("pos"), pos}, {std::hash<std::string>{}("size"), size}});
    unsigned			posTTL = 0;

    std::cout << "player#23 => " << player << std::endl;

    pos = player.delComponent("pos");
    player.addComponent("pos", pos);

    std::cout << "player#23 => " << player << std::endl;

    player["pos"].setAttr<unsigned short>("TTL", std::move(posTTL));

    if (player["pos"].hasAttr("TTL"))
      std::cout << "player#23 => " << player << std::endl;
    std::cout << std::endl;
    {
      ecs::component::Component<ct::TypesWrapper<std::uint16_t, std::uint16_t, std::uint16_t>, ::x, ::y, ::ttl>	c0(pos);
      std::string												s = "qweqwe";
      ecs::component::Component<ct::TypesWrapper<std::string>, ::x>						c1(std::move(s));
      ecs::component::Component<ct::TypesWrapper<std::uint16_t, std::uint16_t>, ::x, ::ttl>			c2(pos);

      std::cout << "c0: " << c0 << std::endl;
      c0.setAttr<::x>(0);
      c0.setAttr<::y>(1);
      c0.setAttr<::ttl>(0x21);
      std::cout << "c0: " << c0 << std::endl;

      std::cout << "c1: " << c1 << std::endl;
      std::cout << std::boolalpha << "is 's' empty => " << s.empty() << std::noboolalpha << std::endl;

      std::cout << "c2: " << c2 << std::endl;
      std::cout << std::endl;
      {
	ecs::component::Vector2 const	pos(23, 42);
	ecs::component::Vector2		size(32, 24);
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
	std::cout << "player#23 => " << player << std::endl;
	player = mutablePlayer;
	std::cout << "player#23 => " << player << std::endl;
	std::cout << std::endl;
      }
      {
	ecs::database::Entity		db_moveTest({{std::hash<std::string>{}(::moveTest), ecs::database::Component(std::forward_as_tuple(std::string("qweqwe")), ::moveTest)}});
	ecs::entity::MoveTest		ct_moveTest(db_moveTest);
	ecs::entity::RTEntity		rt_moveTest;

	std::cout << "db_moveTest => " << db_moveTest << std::endl
		  << "ct_moveTest => " << ct_moveTest << std::endl
		  << "rt_moveTest => " << rt_moveTest << std::endl;
	db_moveTest = std::move(ct_moveTest);
	std::cout << "db_moveTest => " << db_moveTest << std::endl
		  << "ct_moveTest => " << ct_moveTest << std::endl
		  << "rt_moveTest => " << rt_moveTest << std::endl;
	ct_moveTest = std::move(db_moveTest);
	std::cout << "db_moveTest => " << db_moveTest << std::endl
		  << "ct_moveTest => " << ct_moveTest << std::endl
		  << "rt_moveTest => " << rt_moveTest << std::endl;
	db_moveTest = std::move(ct_moveTest);
	rt_moveTest.assign(std::move(db_moveTest), ct::TypesWrapper<ecs::component::MoveTest>(), ::moveTest);
	std::cout << "db_moveTest => " << db_moveTest << std::endl
		  << "ct_moveTest => " << ct_moveTest << std::endl
		  << "rt_moveTest => " << rt_moveTest << std::endl;
	std::cout << std::endl;
      }
    }
  }
}

int	main(void)
{
  test();
  return 0;
}
