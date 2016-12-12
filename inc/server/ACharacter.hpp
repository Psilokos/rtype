//
// ACharacter.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  2 18:07:18 2016 Quentin Rochefort
// Last update Sat Dec 10 20:29:02 2016 Quentin Rochefort
//

#ifndef __ACHARACTER_HPP__
# define __ACHARACTER_HPP__

# include "AElement.hpp"
# include "Weapon.hpp"

namespace	character
{

  enum		eMove {
    LEFT,
    UP,
    DOWN,
    RIGHT
  };
  
  class					ACharacter : public map::AElement
  {

  protected:

    weapon::Weapon			*_weapon;
    unsigned				_hp;
    unsigned				_speed;

  public:

    ACharacter(const int id, const std::pair<unsigned, unsigned> &pos,
	       const std::pair<unsigned, unsigned> &hitbox, weapon::Weapon *weapon,
	       const unsigned hp = 100, const unsigned speed = 10) : AElement(id, pos, hitbox) {
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const unsigned posX, const unsigned posY,
	       const std::pair<unsigned, unsigned> &hitbox, weapon::Weapon *weapon,
	       const unsigned hp = 100, const unsigned speed = 10) : AElement(id, std::make_pair(posX, posY), hitbox) {
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const std::pair<unsigned, unsigned> &pos, const unsigned sizeX,
	       const unsigned sizeY, weapon::Weapon *weapon, const unsigned hp = 100,
	       const unsigned speed = 10) : AElement(id, pos, std::make_pair(sizeX, sizeY)) {
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const unsigned posX, const unsigned posY, const unsigned sizeX,
	       const unsigned sizeY, weapon::Weapon *weapon, const unsigned hp = 100,
	       const unsigned speed = 10) : AElement(id, std::make_pair(posX, posY), std::make_pair(sizeX, sizeY)) {
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const ACharacter &other) = delete;

    virtual ~ACharacter(void) { delete _weapon; }
  
    unsigned				getHp(void) const { return _hp; }
    void				setHp(const unsigned hp) { _hp = hp; }

    unsigned				getSpeed(void) const { return _speed; }
    void				setSpeed(const unsigned speed) { _speed = speed; }

    weapon::Weapon			&getWeapon(void) const { return *_weapon; }
    virtual void			setWeapon(weapon::Weapon *weapon) = 0;

    // virtual unsigned		       	takeDamage(void) = 0;
    // virtual void		       	takePowerUp(void) = 0;
    // virtual void		       	shoot(void) = 0;
    
    ACharacter&				operator=(const ACharacter &other) = delete;
  
  };

}

#endif /* !__ACHARACTER_HPP__ */
