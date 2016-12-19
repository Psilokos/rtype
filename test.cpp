//
// test.cpp for  in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Nov 29 11:48:30 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 18 18:46:50 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "Entity.hpp"

constexpr char	test[] = "test";

namespace	entity_component_system::component
{
  template<typename T>
  using Test = Component<ct::TypesWrapper<T>, ::test>;
}

namespace	entity_component_system::entity
{
  template<typename T>
  using Test = CTEntity<ct::TypesWrapper<ecs::component::Test<T>>, ::test>;
}

TEST(CompileTime, DefaultCtors)
{
  ecs::entity::Test<std::string>	e_test(0, ecs::component::Test<std::string>(0, "qweqwe"));
  ecs::entity::Test<std::string>	e_test0;
  ecs::entity::Test<std::string>	e_test1(e_test);
  ecs::entity::Test<std::string>	e_test2(std::move(e_test));

  EXPECT_STREQ("", e_test.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("", e_test0.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test1.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test2.getComponent<::test>().getAttr<::test>().c_str());
  unsigned lol;
  e_test.getComponent<::test>().serialize(3, lol);
}

TEST(CompileTime, SerializationDeserialization)
{
  ecs::component::Test<unsigned>			c_test;
  byte *						buf;
  unsigned						size;

  c_test.setAttr<::test>(0xDeadB0BE);
  buf = (byte *)c_test.serialize(0, size);
  EXPECT_EQ(0xDeadB0BE, ecs::component::Test<unsigned>::deserialize(buf, size)->getAttr<::test>());
  delete[] buf;
}

TEST(CompileTime, DefaultAssignementOperators)
{
  ecs::entity::Test<std::string>	e_test(42, ecs::component::Test<std::string>(42, "qweqwe"));
  ecs::entity::Test<std::string>	e_test0;
  ecs::entity::Test<std::string>	e_test1(e_test);
  ecs::entity::Test<std::string>	e_test2(std::move(e_test));

  e_test0 = e_test1;
  e_test = std::move(e_test2);
  EXPECT_STREQ("qweqwe", e_test.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test0.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test1.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("", e_test2.getComponent<::test>().getAttr<::test>().c_str());
}

TEST(CompileTime, GetSetComponentAttr)
{
  std::string				s = "petit cochon";
  ecs::entity::Test<std::string>	e_test;
  ecs::component::Test<std::string>	c_test;

  e_test.setComponent<::test>(std::move(e_test.getComponent<::test>() = decltype(c_test)(0xDeadBabe, std::move(s))));
  EXPECT_STREQ("", s.c_str());
  EXPECT_STREQ("petit cochon", e_test.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("", c_test.getAttr<::test>().c_str());
  c_test.setAttr<::test>("gentil petit");
  EXPECT_STREQ("gentil petit", c_test.getAttr<::test>().c_str());
}

TEST(CompileTime, OtherTypesCompatibility)
{
  ecs::database::Entity			e_db(0, {{std::hash<std::string>{}("test"), ecs::database::Component(0xDeadBeef, std::forward_as_tuple(std::string("qweqwe")), "test")}});
  ecs::entity::RTEntity			e_rt(0, std::tuple<ecs::component::Test<std::string>>(ecs::component::Test<std::string>(0xB00B, "cuicui")), "test");
  ecs::entity::Test<std::string>	e_test0(e_db);
  ecs::entity::Test<std::string>	e_test1(e_rt);
  ecs::entity::Test<std::string>	e_test2(std::move(e_db));
  ecs::entity::Test<std::string>	e_test3(std::move(e_rt));

  EXPECT_STREQ("", e_db["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("", e_rt.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test0.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("cuicui", e_test1.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("qweqwe", e_test2.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("cuicui", e_test3.getComponent<::test>().getAttr<::test>().c_str());
}

TEST(RunTime, DefaultCtors)
{
  ecs::entity::RTEntity		e_test(42, std::tuple<ecs::component::Test<std::string>>(ecs::component::Test<std::string>(0xDead, "meow?")), "test");
  ecs::entity::RTEntity		e_test0;
  ecs::entity::RTEntity		e_test1(e_test);
  ecs::entity::RTEntity		e_test2(std::move(e_test));

  EXPECT_FALSE(e_test.hasComponent("test"));
  EXPECT_STREQ("meow?", e_test1.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("meow?", e_test2.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
}

TEST(RunTime, DefaultAssignementOperators)
{
  ecs::entity::RTEntity		e_test(21, std::tuple<ecs::component::Test<std::string>>(ecs::component::Test<std::string>(0xB00B5, "Ron-ron...! <3")), "test");
  ecs::entity::RTEntity		e_test0;
  ecs::entity::RTEntity		e_test1(e_test);
  ecs::entity::RTEntity		e_test2(std::move(e_test));

  e_test0 = e_test1;
  e_test = std::move(e_test2);
  EXPECT_STREQ("Ron-ron...! <3", e_test.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("Ron-ron...! <3", e_test0.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("Ron-ron...! <3", e_test1.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_FALSE(e_test2.hasComponent("test"));
}

TEST(RunTime, GetSetComponentAttr)
{
  std::string				s = "lorem ipsum du foie de veau";
  ecs::entity::RTEntity			e_test;
  ecs::component::Test<std::string>	c_test;

  e_test.addComponent("test", decltype(c_test)());
  e_test.setComponent("test", std::move(e_test.getComponent<decltype(c_test)>("test") = decltype(c_test)(23, std::move(s))));
  EXPECT_STREQ("", s.c_str());
  EXPECT_STREQ("lorem ipsum du foie de veau", e_test.getComponent<decltype(c_test)>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("", c_test.getAttr<::test>().c_str());
  c_test.setAttr<::test>("gentil petit");
  EXPECT_STREQ("gentil petit", c_test.getAttr<::test>().c_str());
}

TEST(RunTime, OtherTypesCompatibility)
{
  ecs::database::Entity			e_db(42, {{std::hash<std::string>{}("test"), ecs::database::Component
									     (30, std::forward_as_tuple(std::string("bonjour les enfants, aujourd'hui nous allons nous epanuir dans un champs fleuri")), "test")}});
  ecs::entity::Test<std::string>	e_ct(21, ecs::component::Test<std::string>(21, ", sous un ciel rose fluo, empreint d'un feu d'artifice naturel... :)"));
  ecs::entity::RTEntity			e_test0(e_db, ct::TypesWrapper<ecs::component::Test<std::string>>(), "test");
  ecs::entity::RTEntity			e_test1(e_ct);
  ecs::entity::RTEntity			e_test2(std::move(e_db), ct::TypesWrapper<ecs::component::Test<std::string>>(), "test");
  ecs::entity::RTEntity			e_test3(std::move(e_ct));

  EXPECT_STREQ("", e_db["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("", e_ct.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("bonjour les enfants, aujourd'hui nous allons nous epanuir dans un champs fleuri", e_test0.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ(", sous un ciel rose fluo, empreint d'un feu d'artifice naturel... :)", e_test1.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("bonjour les enfants, aujourd'hui nous allons nous epanuir dans un champs fleuri", e_test2.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ(", sous un ciel rose fluo, empreint d'un feu d'artifice naturel... :)", e_test3.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
}

TEST(DatabaseData, DefaultCtors)
{
  ecs::database::Entity		e_test(21, {{std::hash<std::string>{}("test"), ecs::database::Component(1, std::forward_as_tuple(std::string("je viens d'une mechante DB!")), "test")}});
  ecs::database::Entity		e_test0;
  ecs::database::Entity		e_test1(e_test);
  ecs::database::Entity		e_test2(std::move(e_test));

  EXPECT_FALSE(e_test.hasComponent("test"));
  EXPECT_STREQ("je viens d'une mechante DB!", e_test1["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("je viens d'une mechante DB!", e_test2["test"].getAttr<std::string>("test").c_str());
}

TEST(DatabaseData, DefaultAssignementOperators)
{
  ecs::database::Entity		e_test(84, {{std::hash<std::string>{}("test"), ecs::database::Component(2, std::forward_as_tuple(std::string("BOUH, mechante DB, BOUH!")), "test")}});
  ecs::database::Entity		e_test0;
  ecs::database::Entity		e_test1(e_test);
  ecs::database::Entity		e_test2(std::move(e_test));

  e_test0 = e_test1;
  e_test = std::move(e_test2);
  EXPECT_STREQ("BOUH, mechante DB, BOUH!", e_test["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("BOUH, mechante DB, BOUH!", e_test0["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("BOUH, mechante DB, BOUH!", e_test1["test"].getAttr<std::string>("test").c_str());
  EXPECT_FALSE(e_test2.hasComponent("test"));
}

TEST(DatabaseData, GetSetComponentAttr)
{
  std::string			s = "si ca se trouve c'est bon... :)";
  ecs::database::Entity		e_test;
  ecs::database::Component	c_test(4, std::tuple<std::string>(), "test");

  e_test.addComponent("test", c_test);
  e_test.setComponent("test", std::move(e_test["test"] = ecs::database::Component(3, std::forward_as_tuple(std::move(s)), "test")));
  EXPECT_STREQ("", s.c_str());
  EXPECT_STREQ("si ca se trouve c'est bon... :)", e_test["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("", c_test.getAttr<std::string>("test").c_str());
  c_test.setAttr<std::string>("test", "MAIS OUAIS DE OUF!");
  EXPECT_STREQ("MAIS OUAIS DE OUF!", c_test.getAttr<std::string>("test").c_str());
}

TEST(DatabaseData, OtherTypesCompatibility)
{
  ecs::entity::Test<std::string>	e_ct(84, ecs::component::Test<std::string>(84, "il etait une fois un extraterreste..."));
  ecs::entity::RTEntity			e_rt(84, std::tuple<ecs::component::Test<std::string>>(ecs::component::Test<std::string>(5, "...intraterreste......")), "test");
  ecs::database::Entity			e_test0(e_ct);
  ecs::database::Entity			e_test1(e_rt, ct::TypesWrapper<ecs::component::Test<std::string>>(), "test");
  ecs::database::Entity			e_test2(std::move(e_ct), ct::TypesWrapper<ecs::component::Test<std::string>>(), "test");
  ecs::database::Entity			e_test3(std::move(e_rt), ct::TypesWrapper<ecs::component::Test<std::string>>(), "test");

  EXPECT_STREQ("", e_ct.getComponent<::test>().getAttr<::test>().c_str());
  EXPECT_STREQ("", e_rt.getComponent<ecs::component::Test<std::string>>("test").getAttr<::test>().c_str());
  EXPECT_STREQ("il etait une fois un extraterreste...", e_test0["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("...intraterreste......", e_test1["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("il etait une fois un extraterreste...", e_test2["test"].getAttr<std::string>("test").c_str());
  EXPECT_STREQ("...intraterreste......", e_test3["test"].getAttr<std::string>("test").c_str());
}

int	main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
