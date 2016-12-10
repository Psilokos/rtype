//
// IWeapon.hpp for AWeapon in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Tue Dec  6 17:30:58 2016 Quentin Rochefort
// Last update Fri Dec  9 15:37:01 2016 Quentin Rochefort
//

#ifndef __IWEAPON_HPP__
# define __IWEAPON_HPP__

namespace	weapon
{
  
  class		IWeapon
  {
    
  protected:

    unsigned	_damage;
    unsigned	_speed;

  public:
    
    virtual ~IWeapon(void) {}
    
    virtual unsigned	getDamage(void) const = 0;
    virtual void	setDamage(const unsigned damage) = 0;

    virtual unsigned	getSpeed(void) const = 0;
    virtual void	setSpeed(const unsigned speed) = 0;
    
  };
  
}

#endif /* !__AWEAPON_HPP__ */
