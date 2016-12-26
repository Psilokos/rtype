/*
** spriteLoader.hpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Wed Dec 14 17:37:48 2016 dufour_n
** Last update Wed Dec 14 17:37:48 2016 dufour_n
*/

#ifndef _SPRITELOADER_HPP_
# define _SPRITELOADER_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>
#include <map>

typedef enum {

} SPRITE_TYPE;

class SpriteLoader {
    private:
        std::map<SPRITE_TYPE, sf::Texture>   _sprites;

        void    parseLine(std::string &line, std::vector<std::string> &);
        void    getSprite(std::string &line, std::vector<std::string> &);

    public:
        SpriteLoader();
        ~SpriteLoader() {};

        void        readFile(std::string &name);
        sf::Texture &operator[](SPRITE_TYPE);
        bool        hasSprite(SPRITE_TYPE arg) const;
};
#endif
