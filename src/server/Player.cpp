//
// Player.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/src/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 31 03:14:21 2016 Quentin Rochefort
// Last update Sat Dec 31 16:26:54 2016 Quentin Rochefort
//

#include <cstdlib>
#include <ctime>
#include "Player.hpp"

namespace	character
{

  Player::PowerEffect	Player::_takeEffect = {
    {map::HP_PLUS, &Player::hpPlus},
    {map::O_WEAPON, &Player::otherWeapon},
    {map::O_BULLET, &Player::otherBullet},
    {map::BULLET_PLUS, &Player::bulletPlus},
    {map::SPEED_PLUS, &Player::speedPlus}
  };

  void	Player::hpPlus(void)
  {
    std::srand(std::time(0));
    _hp += std::rand() % 40 + 10;
    _hp = _hp > 100 ? 100 : _hp;
  }

  void	Player::otherWeapon(void)
  {
    unsigned	weaponType;
    
    std::srand(std::time(0));
    weaponType = std::rand() % NB_WEAPON;
    delete _weapon;
    _weapon = new weapon::Weapon(static_cast<weapon::eWeaponType>(weaponType), _id);
  }

  void	Player::otherBullet(void)
  {
    unsigned	bulletType;

    std::srand(std::time(0));
    bulletType = std::rand() % NB_WEAPON;
    _weapon->setBullet(new weapon::Bullet(0, static_cast<weapon::eWeaponType>(bulletType), _id));
  }

  void	Player::bulletPlus(void) {}

  void	Player::speedPlus(void)
  {
    std::srand(std::time(0));
    _speed += std::rand() % 14 + 1;
  }
  
}
