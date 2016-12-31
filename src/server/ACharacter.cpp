//
// ACharacter.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/src/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 31 02:07:50 2016 Quentin Rochefort
// Last update Sat Dec 31 02:38:04 2016 Quentin Rochefort
//

#include "Enemy.hpp"

namespace	character
{

  bool	ACharacter::takeDamage(const weapon::Bullet * bullet)
  {
    if (static_cast<int>(_hp) - bullet->getDamage() <= 0)
      return 0;
    _hp -= bullet->getDamage();
    return 1;
  }

  weapon::Bullet	*ACharacter::shoot(void)
  {
    weapon::Bullet	*bullet = _weapon->getBullet();

    bullet->setPos(std::make_pair(_pos.first, (!dynamic_cast<Enemy *>(this) ? _pos.second + 1 :
					       _pos.second - 1)));
    bullet->setDirection(std::make_pair(0, (!dynamic_cast<Enemy *>(this)) ? 1 : -1));
    return bullet;
  }
  
}
