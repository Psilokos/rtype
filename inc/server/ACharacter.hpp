//
// ACharacter.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  2 18:07:18 2016 Quentin Rochefort
// Last update Sat Dec 31 02:53:34 2016 Quentin Rochefort
//

#ifndef __ACHARACTER_HPP__
# define __ACHARACTER_HPP__

# include "AElement.hpp"
# include "Weapon.hpp"
# include "Powerup.hpp"

namespace	character
{
  
  class					ACharacter : public map::AElement
  {
    
  protected:

    weapon::Weapon			*_weapon;
    unsigned				_hp;
    unsigned				_score;

  public:

    ACharacter(const int id, const std::pair<unsigned, unsigned> &pos,
	       const std::pair<unsigned, unsigned> &hitbox, weapon::Weapon *weapon,
	       const unsigned hp = 100, const unsigned speed = 5) : AElement(id, pos, hitbox, speed,
									      std::make_pair(0, 0)) {
      _weapon = weapon;
      _hp = hp; }
    ACharacter(const ACharacter &other) = delete;

    virtual ~ACharacter(void) { delete _weapon; }
  
    unsigned				getHp(void) const { return _hp; }
    void				setHp(const unsigned hp) { _hp = hp; }

    weapon::Weapon			&getWeapon(void) const { return *_weapon; }

    unsigned				getScore(void) const { return _score; }
    void				setScore(const unsigned score) { _score = score; }

    virtual bool				takeDamage(const weapon::Bullet *bullet);
    
    virtual weapon::Bullet			*shoot(void);
    
    ACharacter&				operator=(const ACharacter &other) = delete;
  
  };

}

#endif /* !__ACHARACTER_HPP__ */
