//
// Enemy.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/src/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec 20 16:03:33 2016 Quentin Rochefort
// Last update Fri Dec 23 16:02:24 2016 Quentin Rochefort
//

#include <cstdlib>
#include <ctime>
#include "Enemy.hpp"

namespace	character
{

  Enemy::PoMap	Enemy::_setMap = {
    {SOLDIER, &Enemy::setNoPowerup},
    {ALIEN, &Enemy::setRandPowerup},
    {WARRIOR, &Enemy::setNoPowerup}
  };

  std::map<eEnemyType, std::pair<unsigned, unsigned> >	Enemy::_setHitbox = {
    {SOLDIER, std::make_pair(1, 1)},
    {ALIEN, std::make_pair(2, 2)},
    {WARRIOR, std::make_pair(2, 1)}
  };
  
  void	Enemy::setNoPowerup(void)
  {
    _powerup = NULL;
    _score = 100;
  }

  void	Enemy::setRandPowerup(void)
  {
    unsigned	powerupType;
    
    std::srand(std::time(0));
    powerupType = std::rand() % NBPOWERUP;
    _powerup = new map::Powerup(0, _pos, static_cast<map::ePowerupType>(powerupType));
    _score = 200;
  }
  
}
