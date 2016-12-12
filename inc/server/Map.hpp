//
// Map.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 17:55:44 2016 Quentin Rochefort
// Last update Mon Dec 12 19:27:38 2016 Quentin Rochefort
//

#ifndef __MAP_HPP__
# define _MAP_HPP__

# include <list>
# include <vector>
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

  private:

    const unsigned	_sizeY;
    std::map<unsigned, std::list<map::AElement *> >	_entities;
    //std::vector<character::Player *>	_players;

  public:

    Map(const unsigned sizeY = 15);

    ~Map(void) {}

    unsigned	getSizeY(void) const { return _sizeY; }

    //std::list<std::list<map::IElement *> >	&getEntities(void) const { return _entities; }

    //std::vector<character::Player *>	&getPlayers(void) const { return _players; }

    int		generate(const std::string &mapName = "stage1", const eGenType genType = STAGE);
    void	affMap(void) const;
    
    //void	update(void);
    
  };
  
}

#endif /* !__MAP_HPP__ */
