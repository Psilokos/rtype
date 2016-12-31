//
// Block.hpp for R-TYPE in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Thu Dec  1 20:10:13 2016 Quentin Rochefort
// Last update Sat Dec 31 16:26:13 2016 Quentin Rochefort
//

#ifndef __BLOCK_HPP__
# define __BLOCK_HPP__

# include "AElement.hpp"
# include "BlockType.hpp"

# define SCROLL_SPEED	(unsigned)1

namespace	map
{
  
  class		Block : public AElement
  {

  private:

    std::pair<unsigned, unsigned>	setHitboxBlock(const eBlockType blockType);
    
  public:

    Block(const unsigned id, const std::pair<unsigned, unsigned> &pos,
	  const eBlockType blockType) : AElement(id, pos, setHitboxBlock(blockType), SCROLL_SPEED,
						 std::make_pair(0, -1)) { _pattern = new Pattern(map::SCROLL); }
    Block(const Block &other) = delete;
    
    virtual ~Block(void) {}

    virtual void	update(const bool stopScroll);

    Block	&operator=(const Block &other) = delete;
  };
  
}

#endif /* !__BLOCK_HPP__ */
