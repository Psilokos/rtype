//
// Map.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 18:18:17 2016 Quentin Rochefort
// Last update Sat Dec 10 16:56:24 2016 Quentin Rochefort
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Map.hpp"

namespace	map
{

  Map::Map(const unsigned stageNb, const unsigned sizeY) : _stageNb(stageNb), _sizeY(sizeY)
  {
    _hitboxBlock[VOID] = std::make_pair(1, 3);
    _hitboxBlock[MINRECT] = std::make_pair(1, 3);
    _hitboxBlock[LITRECT] = std::make_pair(2, 3);
    _hitboxBlock[SQUARE] = std::make_pair(3, 3);
    _hitboxBlock[ENTRY] = std::make_pair(5, 6);
    _hitboxBlock[ROW] = std::make_pair(8, 6);
    _hitboxBlock[COLUMN] = std::make_pair(3, 9);
  }

  int	Map::generate(__attribute__((__unused__))const eGenType genType)
  {
    std::ifstream	file;
    std::ostringstream	os;
    char		block;
    bool		isRoof = true;

    os << "maps/stage" << _stageNb << ".map";
    file.open(os.str());
    if (!file.is_open())
      return 1;
    while (file.get(block))
      {
	if (block == '\n')
	  {
	    isRoof = false;
	    continue;
	  }
	int i = static_cast<eBlockType>(block - 48);
      }
    file.close();
    return 0;
  }
  
}
