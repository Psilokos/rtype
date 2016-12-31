//
// Map.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 17:55:44 2016 Quentin Rochefort
// Last update Sat Dec 31 18:52:54 2016 Quentin Rochefort
//

#ifndef __MAP_HPP__
# define _MAP_HPP__

# include <list>
# include <map>
# include <string>
# include "Block.hpp"
# include "Player.hpp"

namespace	map
{

  enum		eGenType {
    STAGE,
    PROC
  };
  
  class		Map
  {

  public:

    typedef std::map<unsigned, std::list<map::AElement *> >::iterator	entitiesIt;
    
  private:
    
    const unsigned	_sizeY;
    const unsigned	_viewX;
    std::string		_name;
    unsigned		_sizeX;
    std::map<unsigned, std::list<map::AElement *> >	_entities;
    std::list<character::ACharacter *>	_players;
    std::list<map::AElement *>	_unloadArea;

    bool	checkIsSpace(entitiesIt it, entitiesIt it2, std::pair<unsigned, unsigned> pos, unsigned typeEnemy);
    
  public:

    Map(const unsigned sizeY = 15, const unsigned viewX = 30);

    ~Map(void) {}

    unsigned	getSizeY(void) const { return _sizeY; }

    std::map<unsigned, std::list<map::AElement *> >	&getEntities(void) { return _entities; }
    std::list<map::AElement *>				&getEntitiesByX(const unsigned x) { return _entities[x]; }
    std::list<character::ACharacter *>			&getPlayers(void) { return _players; }

    int       	generateBlocks(const std::string &mapName = "stage1", const eGenType genType = STAGE);
    //int		generateEnemies(unsigned nbEnemies = 35, const unsigned startGenX = 15,
    //				const unsigned tries = 10);
  //int		generatePlayers(const std::list<std::string> &userNames) {}
    void	affMap(void) const;
    
    int		update(void);
    
  };
  
}

#endif /* !__MAP_HPP__ */
