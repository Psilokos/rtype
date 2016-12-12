//
// BlockType.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 16:20:36 2016 Quentin Rochefort
// Last update Mon Dec 12 01:22:27 2016 Quentin Rochefort
//

#ifndef __BLOCKTYPE_HPP__
# define __BLOCKTYPE_HPP__

namespace	map
{
  
  enum	 eBlockType {	// x/y => hitbox
    VOID = 0,           // 3/1
    MINRECT = 1,       	// 3/1 
    LITRECT = 2,       	// 3/2
    SQUARE = 3,		// 3/3
    ENTRY = 4,		// 5/6
    ROW = 5,		// 8/6
    COLUMN = 6		// 3/9    
  };
  
}

#endif /* !__BLOCKTYPE_HPP__ */
