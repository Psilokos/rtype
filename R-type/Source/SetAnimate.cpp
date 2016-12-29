#include "Render.hpp"

int Render::SetAnimate()
{
    AnimationDown.setSpriteSheet(_SpaceWalkerTexture);
    AnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    AnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    AnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    AnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    AnimationUp.setSpriteSheet(_SpaceWalkerTexture);
    AnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    AnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    AnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    AnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    LaserAnimation.setSpriteSheet(_LaserTexture);
    LaserAnimation.addFrame(sf::IntRect(32, 96, 32, 32));
    LaserAnimation.addFrame(sf::IntRect(64, 96, 32, 32));
    LaserAnimation.addFrame(sf::IntRect(32, 96, 32, 32));
    LaserAnimation.addFrame(sf::IntRect( 0, 96, 32, 32));

    currentAnimation = &AnimationDown;
    currentLaserAnimation = &LaserAnimation;

    SpaceWalkerspeed = 20.f;
    Laserspeed = 2500.f;
    
    SpaceWalkermovement.x = 0.f;
    SpaceWalkermovement.y = 0.f;

    Lasermovement.x = 0.f;
    Lasermovement.y = 0.f;
return 0;
}