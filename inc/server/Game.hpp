//
// Game.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 23 14:37:23 2016 Quentin Rochefort
// Last update Sat Dec 31 15:44:51 2016 Quentin Rochefort
//

#ifndef __GAME_HPP__
# define __GAME_HPP__

# include "Map.hpp"

namespace	game
{

  class		Game
  {

  private:

    std::list<map::Map *>	_games;
    
  };
  
}

#endif /* !__GAME_HPP__ */
