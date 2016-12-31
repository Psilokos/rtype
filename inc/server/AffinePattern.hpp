//
// AffinePattern.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 23 13:22:29 2016 Quentin Rochefort
// Last update Fri Dec 23 14:04:37 2016 Quentin Rochefort
//

#ifndef __AFFINEPATTERN_HPP__
# define __AFFINEPATTERN_HPP__

# include <utility>
# include "Pattern.hpp"

namespace	map
{
  
  class		AffinePattern : public Pattern
  {

  private:

    int		_vX;
    int		_vY;

  public:

    AffinePattern(const std::pair<int, int> dir) : Pattern(map::AFFINE) {
      _vX = dir.first;
      _vY = dir.second;
    }
    AffinePattern(const AffinePattern &other) : Pattern(map::AFFINE) {
      _vX = other._vX;
      _vY = other._vY;
    }

    virtual ~AffinePattern(void) {}

    std::pair<int, int>	getDir(void) const { return std::make_pair(_vX, _vY); }
    void		setDir(const std::pair<int, int> &dir) {
      _vX = dir.first;
      _vY = dir.second;
    }

    AffinePattern&	operator=(const AffinePattern &other) {
      _vX = other._vX;
      _vY = other._vY;
      return *this;
    }
    
  };
  
}

#endif /* !__AFFINEPATTERN_HPP__ */
