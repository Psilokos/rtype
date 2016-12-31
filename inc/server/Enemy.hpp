//
// Enemy.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 18:04:58 2016 Quentin Rochefort
// Last update Sat Dec 31 16:10:24 2016 Quentin Rochefort
//

#ifndef __ENEMY_HPP__
# define __ENEMY_HPP__

# include "ACharacter.hpp"

# define NB_ENEMIES_TYPE	(unsigned)3

namespace	character
{

  enum		eEnemyType {
    SOLDIER,
    ALIEN,
    WARRIOR
  };
  
  class		Enemy : public ACharacter
  {

  public:

    typedef std::map<eEnemyType, void (Enemy::*)(void)> PoMap;
    static std::map<eEnemyType, std::pair<unsigned, unsigned> >	_setHitbox;
    
  private:

    map::Powerup	*_powerup;

    static PoMap	_setMap;
 
    inline weapon::Weapon		*setAttribute(const eEnemyType enemyType, const int id)
    {
      switch (enemyType)
	{
	case SOLDIER:
	  return new weapon::Weapon(weapon::GUN, id);
	case ALIEN:
	  return new weapon::Weapon(weapon::LASER, id);
	case WARRIOR:
	  return new weapon::Weapon(weapon::RAPIDGUN, id);
	default:
	  return new weapon::Weapon(weapon::GUN, id);
	}
      return new weapon::Weapon(weapon::GUN, id);
    }
    inline void	setNoPowerup(void);
    void	setRandPowerup(void);
    
  public:

    Enemy(const int id, const std::pair<unsigned, unsigned> &pos,
	  const eEnemyType enemyType) : ACharacter(id, pos,
						   _setHitbox[enemyType],
						   setAttribute(enemyType, id)) { _setMap[enemyType];
      _pattern = new map::AffinePattern(std::make_pair(-1, 0)); }
    Enemy(const Enemy &other) = delete;

    virtual ~Enemy(void) {}

    map::Powerup	*takePowerup(void) { return _powerup; }
    
    Enemy&	operator=(const Enemy &other) = delete;
  
  };

}
#endif /* !__ENEMY_HPP__ */
