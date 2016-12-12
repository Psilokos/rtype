//
// Map.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 18:18:17 2016 Quentin Rochefort
// Last update Mon Dec 12 19:27:37 2016 Quentin Rochefort
//

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Map.hpp"

namespace	map
{

  Map::Map(const unsigned sizeY) : _sizeY(sizeY)
  {
    if (_sizeY < 15)
      throw std::runtime_error("Size Y of the map must be greater than 14");
  }
  
  int			Map::generate(const std::string &mapName, eGenType)
  {
    std::ifstream	file;
    char		block;
    bool		isRoof = true;
    unsigned	       	posX = 0;

    if (!_entities.empty())
      _entities.clear();
    file.open("./maps/" + mapName + ".map");
    if (!file.is_open())
      return 1;
    while (file.get(block))
      {
	if (block == '\n')
	  {
	    isRoof = false;
	    posX = 0;
	    continue;
	  }
	if (_entities.find(posX) == _entities.end())
	  _entities[posX] = (std::list<map::AElement *>(1, new Block(0, std::make_pair(posX, isRoof ? 0 : _sizeY),
								     static_cast<eBlockType>(block - 48))));
	else
	  _entities[posX].push_back(new Block(0, std::make_pair(posX, isRoof ? 0 : _sizeY),
					      static_cast<eBlockType>(block - 48)));
	if (!isRoof)
	  _entities[posX].back()->setPosY(_sizeY - (!_entities[posX].back()->getSizeY() ? 1 :
						    _entities[posX].back()->getSizeY()));
	posX += _entities[posX].back()->getSizeX();
      }
    file.close();
    return 0;
  }

  void					Map::affMap(void) const
  {
    bool				isFound = false;
    std::pair<unsigned, unsigned>	infoX(0, 0);
    unsigned				posX = 0;
    
    for (unsigned y = 0; y != _sizeY; ++y)
      {
	for (auto &it : _entities)
	  {
	    for (auto &it2 : it.second)
	      {
		if (it2->getPosY() <= y and y < it2->getPosY() + it2->getSizeY())
		  {
		    if (it.first != posX)
		      {
			for (unsigned j = posX; j != it.first; ++j)
			  std::cout << " ";
			posX = it.first;
		      }
		    isFound = true;
		    infoX = std::make_pair(it.first, it2->getSizeX());
		    posX += it2->getSizeX();
		    for (unsigned i = 0; i != it2->getSizeX(); ++i)
		      std::cout << "B";
		    break;
		  }
	      }
	    if (!isFound and it.first == infoX.first + infoX.second)
	      {
		std::cout << "   ";
	    	infoX = std::make_pair(it.first, 3);
	    	posX += 3;
	      }
	    isFound = false;
	  }
	std::cout << std::endl;
	posX = 0;
      }
  }
  
}
