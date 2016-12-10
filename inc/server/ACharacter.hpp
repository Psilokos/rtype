//
// ACharacter.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  2 18:07:18 2016 Quentin Rochefort
// Last update Sat Dec 10 16:35:50 2016 Quentin Rochefort
//

#ifndef __ACHARACTER_HPP__
# define __ACHARACTER_HPP__

# include <utility>
# include "IElement.hpp"
# include "IWeapon.hpp"

namespace	character
{

  enum		eMove {
    LEFT,
    UP,
    DOWN,
    RIGHT
  };
  
  class					ACharacter : public map::IElement
  {

  protected:

    const int			       	_id;
    std::pair<unsigned, unsigned>	_pos;
    const std::pair<unsigned, unsigned>	_hitbox;
    weapon::IWeapon			*_weapon;
    unsigned				_hp;
    unsigned				_speed;

  public:

    ACharacter(const int id, const std::pair<unsigned, unsigned> &pos,
	       const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	       const unsigned hp = 100, const unsigned speed = 10) : _id(id), _hitbox(hitbox) {
      _pos = pos;
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const unsigned posX, const unsigned posY,
	       const std::pair<unsigned, unsigned> &hitbox, weapon::IWeapon *weapon,
	       const unsigned hp = 100, const unsigned speed = 10) : _id(id), _hitbox(hitbox) {
      _pos = std::make_pair(posX, posY);
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const std::pair<unsigned, unsigned> &pos, const unsigned sizeX,
	       const unsigned sizeY, weapon::IWeapon *weapon, const unsigned hp = 100,
	       const unsigned speed = 10) : _id(id), _hitbox(std::make_pair(sizeX, sizeY)) {
      _pos = pos;
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const int id, const unsigned posX, const unsigned posY, const unsigned sizeX,
	       const unsigned sizeY, weapon::IWeapon *weapon, const unsigned hp = 100,
	       const unsigned speed = 10) : _id(id), _hitbox(std::make_pair(sizeX, sizeY)) {
      _pos = std::make_pair(posX, posY);
      _weapon = weapon;
      _hp = hp;
      _speed = speed; }
    ACharacter(const ACharacter &other) : _id(other._id), _hitbox(other._hitbox) {
      _pos = other._pos;
      _weapon = other._weapon;
      _hp = other._hp;
      _speed = other._speed; }

    virtual ~ACharacter(void) { delete _weapon; }

    unsigned				getPosX(void) const { return _pos.first; }
    unsigned				getPosY(void) const { return _pos.second; }
    const std::pair<unsigned, unsigned>	&getPos(void) const { return _pos; }

    virtual void		       	setPosX(const unsigned posX) { _pos.first = posX; }
    virtual void		       	setPosY(const unsigned posY) { _pos.second = posY; }
    virtual void		       	setPos(const std::pair<unsigned, unsigned> &pos) { _pos = pos; }

    unsigned				getSizeX(void) const { return _hitbox.first; }
    unsigned				getSizeY(void) const { return _hitbox.second; }
    const std::pair<unsigned, unsigned>	&getSize(void) const { return _hitbox; }

    int					getId(void) const { return _id; }
  
    unsigned				getHp(void) const { return _hp; }
    void				setHp(const unsigned hp) { _hp = hp; }

    unsigned				getSpeed(void) const { return _speed; }
    void				setSpeed(const unsigned speed) { _speed = speed; }

    weapon::IWeapon			&getWeapon(void) const { return *_weapon; }
    virtual void			setWeapon(weapon::IWeapon *weapon) = 0;

    // virtual unsigned		       	takeDamage(void) = 0;
    // virtual void		       	takePowerUp(void) = 0;
    // virtual void		       	shoot(void) = 0;
    
    ACharacter&				operator=(const ACharacter &other) = delete;
  
  };

}

#endif /* !__ACHARACTER_HPP__ */
