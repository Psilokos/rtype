//
// Map.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 17:55:44 2016 Quentin Rochefort
// Last update Sat Dec 10 16:37:18 2016 Quentin Rochefort
//

#ifndef __MAP_HPP__
# define _MAP_HPP__

# include <list>
# include <vector>
# include <map>
# include <utility>
# include "BlockType.hpp"
# include "Player.hpp"

namespace	map
{

  enum		eGenType {
    STAGE,
    PROC
  };
  
  class		Map
  {

  private:

    unsigned		_stageNb;
    const unsigned	_sizeY;
    std::list<std::list<map::IElement *> >	_entities;
    //std::vector<character::Player *>	_players;
    std::map<eBlockType, std::pair<unsigned, unsigned> >	_hitboxBlock;

  public:

    Map(const unsigned stageNb = 1, const unsigned sizeY = 15);

    ~Map(void) {}

    unsigned	getSizeY(void) const { return _sizeY; }
    unsigned	getStageNb(void) const { return _stageNb; }

    //std::list<std::list<map::IElement *> >	&getEntities(void) const { return _entities; }

    //std::vector<character::Player *>	&getPlayers(void) const { return _players; }

    int		generate(const eGenType genType = STAGE);
    
    //void	update(void);
    
  };
  
}

#endif /* !__MAP_HPP__ */
