//
// main.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:27:49 2016 Quentin Rochefort
// Last update Mon Dec 12 19:28:09 2016 Quentin Rochefort
//

#include <iostream>
#include "Map.hpp"

int	main(void)
{
  character::ACharacter	*player = new character::Player(0, std::make_pair(1, 2), std::make_pair(2, 2), NULL);
  map::Map	map;

  map.generate("stage1");
  map.affMap();
  std::cout << std::endl;
  map.generate("stage2");
  map.affMap();
  std::cout << std::endl;
  map.generate("stage3");
  map.affMap();
  std::cout << std::endl;
  map.generate("hardcore");
  map.affMap();
  delete player;
  return 0;
}
