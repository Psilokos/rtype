//
// Weapon.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 10 20:59:03 2016 Quentin Rochefort
// Last update Sat Dec 10 21:46:40 2016 Quentin Rochefort
//

#include "Weapon.hpp"

namespace	weapon
{
  
  Weapon::Weapon(const eWeaponType weaponType)
  {
    switch (weaponType)
      {
      case TYPE1:
	setAttributes(100, 20);
	break;
      case TYPE2:
	setAttributes(80, 30);
	break;
      case TYPE3:
	setAttributes(60, 40);
	break;
      default:
	break;
      }
  }

  void	Weapon::setAttributes(const unsigned damage, const unsigned speed)
  {
    _damage = damage;
    _speed = speed;
  }
  
}
