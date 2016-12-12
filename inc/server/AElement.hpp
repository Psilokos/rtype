//
// AElement.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sat Dec 10 16:33:10 2016 Quentin Rochefort
// Last update Sat Dec 10 21:36:56 2016 Quentin Rochefort
//

#ifndef __AELEMENT_HPP__
# define __AELEMENT_HPP__

# include <utility>

namespace	map
{

  class		AElement
  {

  protected:

    const int				_id;
    std::pair<unsigned, unsigned>	_pos;
    const std::pair<unsigned, unsigned>	_hitbox;
    
  public:

    AElement(const int id, const std::pair<unsigned, unsigned> &pos,
	     const std::pair<unsigned, unsigned> &hitbox) : _id(id), _hitbox(hitbox) {
      _pos = pos; }
    AElement(const AElement &other) = delete;
    
    virtual ~AElement(void) {}

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

    AElement				&operator=(const AElement &other) = delete;
    
  };
  
}

#endif /* !__AELEMENT_HPP__ */
