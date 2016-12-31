//
// Bullet.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Wed Dec 14 19:12:46 2016 Quentin Rochefort
// Last update Sat Dec 31 16:10:23 2016 Quentin Rochefort
//

#ifndef __BULLET_HPP__
# define __BULLET_HPP__

# include <map>
# include "WeaponType.hpp"
# include "AElement.hpp"
# include "AffinePattern.hpp"
# include "SinusoidalPattern.hpp"

namespace	weapon
{
  
  class		Bullet : public map::AElement
  {

  public:

    typedef std::map<eWeaponType, void (Bullet::*)(void)> BuMap;
    
  private:

    unsigned	_damage;
    const int  	_idOwner;

    static BuMap	_setBulletAttributes;
    
    unsigned	setAttributeSpeed(const eWeaponType weaponType);
    void	setGunBullet(void);
    void	setLaserBullet(void);
    void	setRapidGunBullet(void);
    
  public:

    Bullet(const int id, const eWeaponType weaponType, const int idOwner) :
      AElement(id, std::make_pair(0, 0), std::make_pair(1, 1), setAttributeSpeed(weaponType),
	       std::make_pair(0, 0)), _idOwner(idOwner) {}
    Bullet(const Bullet &other) = delete;

    virtual ~Bullet(void) {}

    unsigned	getDamage(void) const { return _damage; }
    void	setDamage(const unsigned damage) { _damage = damage; }

    int		getIdOwner(void) const { return _idOwner; }

    Bullet	&operator=(const Bullet &other) = delete;
    
  };
  
}
  
#endif /* !__BULLET_HPP__ */
