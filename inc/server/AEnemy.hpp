//
// AEnemy.hpp for AEnemy in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 18:04:58 2016 Quentin Rochefort
// Last update Fri Dec  9 16:36:43 2016 Quentin Rochefort
//

#ifndef __AENEMY_HPP__
# define __AENEMY_HPP__

# include "ACharacter.hpp"

namespace	character
{
  
  class		AEnemy : public ACharacter
  {
  
  public:

    AEnemy(const int id, const std::pair<unsigned, unsigned> &pos,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, hitbox, weapon,
									    hp, speed) {}
    AEnemy(const int id, const unsigned posX, const unsigned posY,
	   const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, hitbox,
									    weapon, hp, speed) {}
    AEnemy(const int id, const std::pair<unsigned, unsigned> &pos,
	   const unsigned sizeX, const unsigned sizeY, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, pos, sizeX, sizeY,
									    weapon, hp, speed) {}
    AEnemy(const int id, const unsigned posX, const unsigned posY,
	   const unsigned sizeX, const unsigned sizeY, weapon::IWeapon *weapon,
	   const unsigned hp = 100, const unsigned speed = 10) : ACharacter(id, posX, posY, sizeX,
									    sizeY, weapon, hp,
									    speed) {}
    AEnemy(const AEnemy &other) = delete;

    ~AEnemy(void) {}

    AEnemy&	operator=(const AEnemy &other) = delete;
  
  };

}
#endif /* !__AENEMY_HPP__ */
