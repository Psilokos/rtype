//
// SinusoidalPattern.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 23 13:29:00 2016 Quentin Rochefort
// Last update Fri Dec 23 13:41:28 2016 Quentin Rochefort
//

#ifndef __SINUSOIDALPATTERN_HPP__
# define __SINUSOIDALPATTERN_HPP__

# include "Pattern.hpp"

namespace	map
{

  class		SinusoidalPattern : public Pattern
  {

  private:
    
    const unsigned	_initY;
    float		_freq;
    float		_ampl;
    bool		_dir;

  public:

    SinusoidalPattern(const unsigned initY, const float freq, const float ampl, const bool dir);
    SinusoidalPattern(const SinusoidalPattern &other);

    virtual ~SinusoidalPattern(void) {}

    unsigned		getInitY(void) const { return _initY; }

    float		getFreq(void) const { return _freq; }
    void		setFreq(const float freq) { _freq = freq; }

    float		getAmpl(void) const { return _ampl; }
    void		setAmpl(const float ampl) { _ampl = ampl; }

    bool		getDir(void) const { return _dir; }
    void		setDir(const bool dir) { _dir = dir; }

    SinusoidalPattern&	operator=(const SinusoidalPattern &other) = delete;
    
  };
  
}

#endif /* !__SINUSOIDALPATTERN_HPP__ */
