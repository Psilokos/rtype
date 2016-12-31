//
// Player.hpp for Player in /home/rochef/Projets/C++/r-type/include
// 
// Made by Quentin Rochefort
// Login   <rochef_q@epitech.net>
// 
// Started on  Fri Dec  2 19:10:48 2016 Quentin Rochefort
// Last update Sat Dec 31 16:29:04 2016 Quentin Rochefort
//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

# include "ACharacter.hpp"
# include "WeaponType.hpp"
# include "Powerup.hpp"

namespace	character
{

  class		Player : public ACharacter
  {

  public:

    typedef std::map<map::ePowerupType, void (Player::*)(void)>	PowerEffect;
    
  private:

    static PowerEffect	_takeEffect;

    void	hpPlus(void);
    void	otherWeapon(void);
    void	otherBullet(void);
    void	bulletPlus(void);
    void	speedPlus(void);
    
  public:

    Player(const int id,
	   const std::pair<unsigned, unsigned> &pos) : ACharacter(id, pos, std::make_pair(2, 1),
								  new weapon::Weapon(weapon::GUN, id)) {
      _score = 0;
      _pattern = new map::AffinePattern(std::make_pair(0, 0)); }
    Player(const Player &other) = delete;

    virtual ~Player(void) {}

    virtual void	setWeapon(weapon::Weapon *weapon) { delete _weapon; _weapon = weapon; }

    virtual void       	takePowerup(const map::Powerup *powerup) { _takeEffect[powerup->getEffect()]; }
    
    Player&		operator=(const Player &other) = delete;
    
  };
  
}

#endif /* !__PLAYER_HPP__ */
