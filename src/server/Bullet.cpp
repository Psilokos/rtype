//
// Bullet.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 16 12:04:06 2016 Quentin Rochefort
// Last update Fri Dec 23 14:03:02 2016 Quentin Rochefort
//

#include "Bullet.hpp"

namespace	weapon
{

  Bullet::BuMap	Bullet::_setBulletAttributes = {
    {GUN, &Bullet::setGunBullet},
    {LASER, &Bullet::setLaserBullet},
    {RAPIDGUN, &Bullet::setRapidGunBullet}
  };
  
  unsigned	Bullet::setAttributeSpeed(const eWeaponType weaponType)
  {
    switch (weaponType)
      {
      case GUN:
	return 20;
      case LASER:
	return 25;
      case RAPIDGUN:
	return 40;
      default:
	return 0;
      }
    return 0;
  }

  void	Bullet::setGunBullet(void)
  {
    _damage = 30;
    _pattern = new map::AffinePattern(std::make_pair(0, 0));
  }
  
  void	Bullet::setLaserBullet(void)
  {
    _damage = 50;
    _pattern = new map::SinusoidalPattern(_pos.second, 0.0, 0.0, true);
  }

  void	Bullet::setRapidGunBullet(void)
  {
    _damage = 20;
    _pattern = new map::AffinePattern(std::make_pair(0, 0));
  }
  
}
