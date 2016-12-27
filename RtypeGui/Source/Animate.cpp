/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-24 12:18:39 
 * @Last Modified by:   Stephane.Lejeune 
 * @Last Modified time: 2016-12-24 12:18:39 
 */

#include "Animate.hpp"

Animate::Animate() : m_texture(NULL)
{}

void Animate::addFrame(sf::IntRect rect)
{
    m_frames.push_back(rect);
}

void Animate::setSpriteSheet(const sf::Texture& texture)
{
    m_texture = &texture;
}

const sf::Texture* Animate::getSpriteSheet() const
{
    return m_texture;
}

std::size_t Animate::getSize() const
{
    return m_frames.size();
}

const sf::IntRect& Animate::getFrame(std::size_t n) const
{
    return m_frames[n];
}