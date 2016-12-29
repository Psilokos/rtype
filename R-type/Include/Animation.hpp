/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-24 12:17:40 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-24 12:51:36
 */
 
#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class Animation
{
public:
    Animation();

    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getSize() const;
    const sf::IntRect& getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
};

#endif /* ! ANIMATION_HPP */