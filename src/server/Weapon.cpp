//
// Weapon.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 10 20:59:03 2016 Quentin Rochefort
// Last update Fri Dec 23 12:25:42 2016 Quentin Rochefort
//

#include "Weapon.hpp"

namespace	weapon
{
  
  Weapon::Weapon(const eWeaponType weaponType, const int idOwner)
  {
    switch (weaponType)
      {
      case GUN:
	setAttributes(100);
	break;
      case LASER:
	setAttributes(80);
	break;
      case RAPIDGUN:
	setAttributes(60);
	break;
      default:
	break;
      }
    _bullet = new Bullet(0, weaponType, idOwner);
  }
  
}
