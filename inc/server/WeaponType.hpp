//
// WeaponType.hpp for R-TYPE in /home/rochef/Projets/C++/rtype/inc/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Wed Dec 14 19:29:53 2016 Quentin Rochefort
// Last update Sat Dec 31 15:38:49 2016 Quentin Rochefort
//

#ifndef __WEAPONTYPE_HPP__
# define __WEAPONTYPE_HPP__

# define NB_WEAPON	(unsigned)3

namespace	weapon
{

  enum		eWeaponType {
    GUN,
    LASER,
    RAPIDGUN
  };
  
}

#endif /* !__WEAPONTYPE_HPP__ */
