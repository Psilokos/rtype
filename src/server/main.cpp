//
// main.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:27:49 2016 Quentin Rochefort
// Last update Fri Dec  9 18:41:00 2016 Quentin Rochefort
//

#include <iostream>
#include "Map.hpp"

int	main(void)
{
  character::ACharacter	*player = new character::Player(0, std::make_pair(1, 2), std::make_pair(2, 2), NULL);
  map::Map	map;

  std::cout << player->getHp() << std::endl;
  map.generate();
  delete player;
  return 0;
}
