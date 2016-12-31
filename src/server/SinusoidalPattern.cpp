//
// SinusoidalPattern.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/src/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec 23 13:36:30 2016 Quentin Rochefort
// Last update Fri Dec 23 13:43:15 2016 Quentin Rochefort
//

#include "SinusoidalPattern.hpp"

namespace	map
{

  SinusoidalPattern::SinusoidalPattern(const unsigned initY, const float freq, const float ampl,
				       const bool dir) : Pattern(map::SINUSOIDAL), _initY(initY)
  {
    _freq = freq;
    _ampl = ampl;
    _dir = dir;
  }

  SinusoidalPattern::SinusoidalPattern(const SinusoidalPattern &other) : Pattern(map::SINUSOIDAL), _initY(other._initY)
  {
    _freq = other._freq;
    _ampl = other._ampl;
    _dir = other._dir;
  }
  
}
