//
// Pattern.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 23 12:59:03 2016 Quentin Rochefort
// Last update Fri Dec 23 13:28:43 2016 Quentin Rochefort
//

#ifndef __PATTERN_HPP__
# define __PATTERN_HPP__

namespace	map
{
  
  enum		eNamePattern {
    NONE,
    SCROLL,
    AFFINE,
    SINUSOIDAL
  };
  
  class		Pattern
  {
    
  protected:

    eNamePattern	_namePattern;

  public:

    Pattern(const eNamePattern namePattern) { _namePattern = namePattern; }
    Pattern(const Pattern &other) { _namePattern = other._namePattern; }

    virtual ~Pattern(void) {}

    eNamePattern	getPattern(void) const { return _namePattern; }
    void		setPattern(const eNamePattern namePattern) { _namePattern = namePattern; }
    
    Pattern&	operator=(const Pattern &other) {
      _namePattern = other._namePattern;
      return *this; }
    
  };
  
}

#endif /* !__PATTERN_HPP__ */
