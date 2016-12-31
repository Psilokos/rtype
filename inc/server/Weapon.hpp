//
// Weapon.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:30:58 2016 Quentin Rochefort
// Last update Sat Dec 31 16:27:33 2016 Quentin Rochefort
//

#ifndef __WEAPON_HPP__
# define __WEAPON_HPP__

# include <map>
# include "WeaponType.hpp"
# include "Bullet.hpp"

namespace	weapon
{
  
  class		Weapon
  {
    
  private:

    unsigned	_cadence;
    Bullet	*_bullet;

    void	setAttributes(const unsigned cadence) { _cadence = cadence; }

  public:
    Weapon(const eWeaponType weaponType, const int idOwner);
    Weapon(const Weapon &other) {
      _cadence = other._cadence;
      _bullet = other._bullet;
    }
    
    ~Weapon(void) { delete _bullet; }
    
    unsigned	getCadence(void) const { return _cadence; }
    void	setCadence(const unsigned cadence) { _cadence = cadence; }
    
    Bullet	*getBullet(void) const { return _bullet; }
    void	setBullet(Bullet *bullet) { delete _bullet; _bullet = bullet; }

    Weapon		&operator=(const Weapon &other) {
      _cadence = other._cadence;
      _bullet = other._bullet;
      return *this;
    }
    
  };
  
}

#endif /* !__WEAPON_HPP__ */
