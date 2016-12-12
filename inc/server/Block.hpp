//
// Block.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Thu Dec  1 20:10:13 2016 Quentin Rochefort
// Last update Sun Dec 11 16:58:37 2016 Quentin Rochefort
//

#ifndef __BLOCK_HPP__
# define __BLOCK_HPP__

# include "AElement.hpp"
# include "BlockType.hpp"

namespace	map
{
  
  class		Block : public AElement
  {

  private:

    std::pair<unsigned, unsigned>	setHitboxBlock(const eBlockType blockType);
    
  public:

    Block(const unsigned id, const std::pair<unsigned, unsigned> &pos,
	  const eBlockType blockType) : AElement(id, pos, setHitboxBlock(blockType)) {}
    Block(const Block &other) = delete;
    
    virtual ~Block(void) {}

    Block	&operator=(const Block &other) = delete;
  };
  
}

#endif /* !__BLOCK_HPP__ */
