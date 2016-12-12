//
// Block.cpp for R-TYPE in /home/rochef/Projets/C++/rtype/src/server
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Sun Dec 11 16:40:41 2016 Quentin Rochefort
// Last update Sun Dec 11 20:20:33 2016 Quentin Rochefort
//

#include "Block.hpp"

namespace	map
{

  std::pair<unsigned, unsigned>	Block::setHitboxBlock(const eBlockType blockType)
  {
    switch (blockType)
      {
      case VOID:
	return std::make_pair(3, 0);
      case MINRECT:
	return std::make_pair(3, 1);
      case LITRECT:
	return std::make_pair(3, 2);
      case SQUARE:
	return std::make_pair(3, 3);
      case ENTRY:
	return std::make_pair(5, 6);
      case ROW:
	return std::make_pair(8, 6);
      case COLUMN:
	return std::make_pair(3, 9);
      default:
	return std::make_pair(0, 0);
      }
    return std::make_pair(0, 0);
  }
  
}
