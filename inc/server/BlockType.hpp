//
// BlockType.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  9 16:20:36 2016 Quentin Rochefort
// Last update Sat Dec 10 16:58:17 2016 Quentin Rochefort
//

#ifndef __BLOCKTYPE_HPP__
# define __BLOCKTYPE_HPP__

namespace	map
{
  
  enum	 eBlockType {	// x/y => hitbox
    VOID = 0,           // 1/3
    MINRECT = 1,       	// 1/3 
    LITRECT = 2,       	// 2/3
    SQUARE = 3,		// 3/3
    ENTRY = 4,		// 5/6
    ROW = 5,		// 8/6
    COLUMN = 6		// 3/9    
  };
  
}

#endif /* !__BLOCKTYPE_HPP__ */
