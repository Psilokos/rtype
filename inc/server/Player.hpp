//
// Player.hpp for Player in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  2 19:10:48 2016 Quentin Rochefort
// Last update Fri Dec  9 16:36:26 2016 Quentin Rochefort
//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

# include "ACharacter.hpp"

namespace	character
{

  class		Player : public ACharacter
  {

  public:

    Player(const int id, const std::pair<unsigned, unsigned> &pos,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, hitbox, weapon,
									    hp, speed) {}
    Player(const int id, const unsigned posX, const unsigned posY,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, hitbox,
									    weapon, hp, speed) {}
    Player(const int id, const std::pair<unsigned, unsigned> &pos,
	   const unsigned sizeX, const unsigned sizeY, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, sizeX, sizeY,
									    weapon, hp, speed) {}
    Player(const int id, const unsigned posX, const unsigned posY,
	   const unsigned sizeX, const unsigned sizeY, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, sizeX,
									    sizeY, weapon, hp,
									    speed) {}
    Player(const Player &other) = delete;

    virtual ~Player(void) {}

    virtual void	setWeapon(weapon::IWeapon *weapon) { _weapon = weapon; }
    
    Player&		operator=(const Player &other) = delete;
    
  };
  
}

#endif /* !__PLAYER_HPP__ */
