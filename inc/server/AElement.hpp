//
// AElement.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 10 16:33:10 2016 Quentin Rochefort
// Last update Sat Dec 31 16:28:32 2016 Quentin Rochefort
//

#ifndef __AELEMENT_HPP__
# define __AELEMENT_HPP__

# include <utility>
# include "Pattern.hpp"

namespace	map
{

  enum		eMove {
    LEFT,
    UP,
    DOWN,
    RIGHT
  };
  
  class		AElement
  {

  public:
    
    static unsigned	incrId;
    
    static unsigned	assignId(void) { return incrId++; }
    
  protected:

    const int				_id;
    std::pair<unsigned, unsigned>	_pos;
    const std::pair<unsigned, unsigned>	_hitbox;
    unsigned				_speed;
    std::pair<short, short>		_direction;
    Pattern				*_pattern;
    
  public:

    AElement(const int id, const std::pair<unsigned, unsigned> &pos,
	     const std::pair<unsigned, unsigned> &hitbox, unsigned speed,
	     const std::pair<short, short> &direction) : _id(id), _hitbox(hitbox) {
      _pos = pos;
      _speed = speed;
      _direction = direction; }
    AElement(const AElement &other) = delete;
    
    virtual ~AElement(void) { delete _pattern; }

    int					getId(void) const { return _id; }
    
    const std::pair<unsigned, unsigned>	&getPos(void) const { return _pos; }
    unsigned				getPosX(void) const { return _pos.first; }
    unsigned				getPosY(void) const { return _pos.second; }
    virtual void		       	setPosX(const unsigned posX) { _pos.first = posX; }
    virtual void		       	setPosY(const unsigned posY) { _pos.second = posY; }
    virtual void		       	setPos(const std::pair<unsigned, unsigned> &pos) { _pos = pos; }

    unsigned				getSizeX(void) const { return _hitbox.first; }
    unsigned				getSizeY(void) const { return _hitbox.second; }
    const std::pair<unsigned, unsigned>	&getSize(void) const { return _hitbox; }

    unsigned				getSpeed(void) const { return _speed; }
    void				setSpeed(const unsigned speed) { _speed = speed; }

    const std::pair<short, short>      	&getDirection(void) const { return _direction; }
    void				setDirection(const std::pair<short, short> &direction) { _direction = direction; }
    void				setDirectionX(const unsigned dirX) { _direction.first = dirX; }
    void				setDirectionY(const unsigned dirY) { _direction.second = dirY; }

    Pattern				&getPattern(void) const { return *_pattern; }
    void				setPattern(Pattern *pattern) { delete _pattern; _pattern = pattern; }

    AElement				&operator=(const AElement &other) = delete;
    
  };
  
}

#endif /* !__AELEMENT_HPP__ */
