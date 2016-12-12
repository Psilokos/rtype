//
// Enemy.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 18:04:58 2016 Quentin Rochefort
// Last update Sat Dec 10 21:32:38 2016 Quentin Rochefort
//

#ifndef __ENEMY_HPP__
# define __ENEMY_HPP__

# include "ACharacter.hpp"

namespace	character
{
  
  class		Enemy : public ACharacter
  {
  
  public:

    Enemy(const int id, const std::pair<unsigned, unsigned> &pos,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::Weapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, hitbox, weapon,
									    hp, speed) {}
    Enemy(const int id, const unsigned posX, const unsigned posY,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::Weapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, hitbox,
									    weapon, hp, speed) {}
    Enemy(const int id, const std::pair<unsigned, unsigned> &pos,
	   const unsigned sizeX, const unsigned sizeY, weapon::Weapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, sizeX, sizeY,
									    weapon, hp, speed) {}
    Enemy(const int id, const unsigned posX, const unsigned posY,
	   const unsigned sizeX, const unsigned sizeY, weapon::Weapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, sizeX,
									    sizeY, weapon, hp,
									    speed) {}
    Enemy(const Enemy &other) = delete;

    ~Enemy(void) {}

    Enemy&	operator=(const Enemy &other) = delete;
  
  };

}
#endif /* !__ENEMY_HPP__ */
