//
// Powerup.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Wed Dec 14 19:12:12 2016 Quentin Rochefort
// Last update Sat Dec 31 16:10:42 2016 Quentin Rochefort
//

#ifndef __POWERUP_HPP__
# define __POWERUP_HPP__

# include "AElement.hpp"

# define NBPOWERUP	(unsigned)5

namespace	map
{

  enum		ePowerupType {
    HP_PLUS,
    O_WEAPON,
    O_BULLET,
    BULLET_PLUS,
    SPEED_PLUS
  };
  
  class		Powerup : public AElement
  {

  private:

    const ePowerupType	_effect;

  public:

    Powerup(const int id, const std::pair<unsigned, unsigned> &pos, const ePowerupType powerupType) :
      AElement(id, pos, std::make_pair(1, 1), 0, std::make_pair(0, 0)), _effect(powerupType) {
      _pattern = new Pattern(map::SCROLL);
    }
    Powerup(const Powerup &other) = delete;

    virtual ~Powerup(void) {}

    ePowerupType	getEffect(void) const { return _effect; }
    
    Powerup	&operator=(const Powerup &other) = delete;
    
  };
  
}

#endif /* !__POWERUP_HPP__ */
