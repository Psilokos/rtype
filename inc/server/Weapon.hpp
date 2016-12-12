//
// Weapon.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:30:58 2016 Quentin Rochefort
// Last update Sat Dec 10 21:46:37 2016 Quentin Rochefort
//

#ifndef __WEAPON_HPP__
# define __WEAPON_HPP__

namespace	weapon
{

  enum		eWeaponType {
    TYPE1,
    TYPE2,
    TYPE3
  };
  
  class		Weapon
  {
    
  private:

    unsigned	_damage;
    unsigned	_speed;

    void		setAttributes(const unsigned damage, const unsigned speed);

  public:
    Weapon(const eWeaponType weaponType);
    Weapon(const Weapon &other) {
      _damage = other._damage;
      _speed = other._speed;
    }
    
    virtual ~Weapon(void) {}
    
    virtual unsigned	getDamage(void) const = 0;
    virtual void	setDamage(const unsigned damage) = 0;

    virtual unsigned	getSpeed(void) const = 0;
    virtual void	setSpeed(const unsigned speed) = 0;

    Weapon		&operator=(const Weapon &other) {
      _damage = other._damage;
      _speed = other._speed;
      return *this;
    }
    
  };
  
}

#endif /* !__WEAPON_HPP__ */
