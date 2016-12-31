//
// Map.cpp for R-TYPE in /home/rochef/Projets/C++/r-type/src
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 18:18:17 2016 Quentin Rochefort
// Last update Sat Dec 31 18:53:23 2016 Quentin Rochefort
//

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Map.hpp"
#include "Enemy.hpp"

namespace	map
{

  Map::Map(const unsigned sizeY, const unsigned viewX) : _sizeY(sizeY), _viewX(viewX)
  {
    if (_sizeY < 15)
      throw std::runtime_error("Map::Map() : Size Y of the map must be greater than 14");
    if (_viewX < 25)
      throw std::runtime_error("Map::Map() : View X of the map must be greater than 24");
    std::srand(std::time(0));
  }
  
  int			Map::generateBlocks(const std::string &mapName, eGenType)
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
    _name = mapName;
    _sizeX = 0;
    while (file.get(block))
      {
	if (block == '\n')
	  {
	    isRoof = false;
	    if (posX > _sizeX)
	      _sizeX = posX;
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
    if (posX > _sizeX)
      _sizeX = posX;
    file.close();
    return 0;
  }
  
  bool		Map::checkIsSpace(entitiesIt it, entitiesIt it2, std::pair<unsigned, unsigned> pos, unsigned typeEnemy)
  {
    for (auto &it2 : it->second)
      if (it2->getPosY() + it2->getSizeY() > pos.second and (it2->getPosY() > pos.second +
						       character::Enemy::_setHitbox[static_cast<character::eEnemyType>(typeEnemy)].second))
	return false;
    for (auto &it3 : it2->second)
      if (pos.first + character::Enemy::_setHitbox[static_cast<character::eEnemyType>(typeEnemy)].first > it2->first and (it3->getPosY() + it3->getSizeY() > pos.second))
	return false;
    return true;
  }
  
  // int		Map::generateEnemies(unsigned nbEnemies, const unsigned startGenX, const unsigned tries)
  // {
  //   unsigned	posX;
  //   unsigned	posY;
  //   unsigned	typeEnemy;
    
  //   if (_entities.empty())
  //     throw std::runtime_error("Map::generateEnemies() : Generate blocks with function generateBlocks() first");
  //   if (!nbEnemies or !tries)
  //     return 1;
  //   posX = std::rand() % ((static_cast<int>(_sizeX - startGenX) > 0) ?
  // 			  _sizeX - startGenX : _sizeX) + (static_cast<int>(_sizeX - startGenX) > 0
  // 							  ? startGenX : 0);
  //   posY = std::rand() % _sizeY;
  //   typeEnemy = std::rand() % NB_ENEMIES_TYPE;
  //   auto it = _entities.find(posX);
  //   if (!checkIsSpace(--_entities.lower_bound(posX), _entities.lower_bound(posX), std::make_pair(posX, posY), typeEnemy))
  //     {
  // 	//std::cout << "posX : " << posX << " posY: " << posY << " [ko]" << std::endl;
  // 	return generateEnemies(nbEnemies, startGenX, tries - 1);
  //     }
  //   // if (it == _entities.end())
  //   //   _entities[posX] = (std::list<map::AElement *>(1, new character::Enemy(0, std::make_pair(posX, posY), static_cast<character::eEnemyType>(typeEnemy))));
  //   // else
  //   //   _entities[posX].push_back(new character::Enemy(0, std::make_pair(posX, posY), static_cast<character::eEnemyType>(typeEnemy)));
  //   //std::cout << "posX : " << posX << " posY: " << posY << " [ok]" << std::endl;
  //   return generateEnemies(nbEnemies - 1, (!(nbEnemies % 2) and _sizeX - startGenX > _viewX) ?
  // 			   startGenX + 3 : startGenX, 10);
  // }
  
  void					Map::affMap(void) const
  {
    bool				isFound = false;
    std::pair<unsigned, unsigned>	infoX(0, 0);
    unsigned				posX = 0;
    
    for (unsigned y = 0; y < _sizeY; ++y)
      {
	for (auto &it : _entities)
	  {
	    for (auto &it2 : it.second)
	      {
		if (it2->getPosY() <= y and y < it2->getPosY() + it2->getSizeY())
		  {
		    if (it.first != posX and posX < it.first)
		      {
			for (unsigned j = posX; j < it.first; ++j)
			  std::cout << " ";
			posX = it.first;
		      }
		    isFound = true;
		    infoX = std::make_pair(it.first, it2->getSizeX());
		    posX += it2->getSizeX();
		    for (unsigned i = 0; i < it2->getSizeX(); ++i)
		      {
			if (!dynamic_cast<character::Enemy *>(it2))
			  std::cout << "B";
			else
			  std::cout << "E";
		      }
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

  int	Map::update(void)
  {
    return 0;
  }
  
}
