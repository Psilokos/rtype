
//
// main.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:27:49 2016 Quentin Rochefort
// Last update Sat Dec 31 18:53:40 2016 Quentin Rochefort
//

#include <exception>
#include <iostream>
#include "Map.hpp"
#include "Enemy.hpp"

#define NB_ENEMIES	(unsigned)35

int	main(int ac, char **av)
{
  if (ac == 1)
    {
      std::cerr << "Usage: " << av[0] << " fileName" << std::endl;
      return 1;
    }
  try {
    map::Map	map;

    if (map.generateBlocks(av[1]))
    {
      std::cerr << "Error: " << av[1] << ".map not found" << std::endl;
      return 1;
    }
    //map.generateEnemies(NB_ENEMIES);
    map.affMap();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
