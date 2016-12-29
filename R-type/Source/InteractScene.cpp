/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:54:03 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-27 00:33:59
 */
 
#include "Render.hpp"

int Render::GetUsername(int state)
{
    static int i = 0;
//std::cout  t'on reboot'
    
    if (state == 0)
    {   
        if (_username.size() == 0 || i == 0 || _reboot == true)
        {
            _username = " ";
            i++;
        }
        else if (_username.size() >= 13 || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            _username.erase(_username.begin());
        else
            _username += static_cast<char>(_event.text.unicode);
            
        if (_event.type == sf::Event::KeyPressed)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    return 2;
    }
return 0;
}

int Render::SelectServer(int state)
{
    static int     choice = 0;


    if (state == 1)
    {
    if (_reboot == true)
        choice = 0;
    if (_event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choice < 1)
            choice++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choice > 0)
            choice--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return choice;

        if (choice == 1)
            _aff_server1.setColor(sf::Color::Red);
        else if (choice == 0)
            _aff_server1.setColor(sf::Color::Green);
    }
return 0;
}

int Render::SelectRoom(int state)
{
    static int     choice = 0;

    if (_reboot == true)
        choice = 0;

    if (state == 2 && _event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choice < 1)
            choice++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choice > 0)
            choice--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return choice;

        if (choice == 1)
            _aff_RoomOne.setColor(sf::Color::Red);
        else if (choice == 0)
            _aff_RoomOne.setColor(sf::Color::Green);
return 0;
}

int Render::Game(int state)
{
    static int i = 0;

    if (_reboot == true)
        i = 0;

    if (i == 0)
    {
        SpaceWalker.setPosition(80.f,230.f);
        Laser.setPosition(SpaceWalker.getPosition().x, SpaceWalker.getPosition().y);
        i++;
    }



    if (SpaceWalkermovement.x >= 200.f)
        SpaceWalkermovement.x -= SpaceWalkerspeed;
    else if (SpaceWalkermovement.y >= 200.f)
        SpaceWalkermovement.y -= SpaceWalkerspeed;
    else if (SpaceWalkermovement.x <= -200.f)
        SpaceWalkermovement.x += SpaceWalkerspeed;
    else if (SpaceWalkermovement.y <= -200.f)
        SpaceWalkermovement.y += SpaceWalkerspeed;

    if (SpaceWalker.getPosition().y >= 720 || SpaceWalker.getPosition().y <= 0)
        return 1;
    else if (SpaceWalker.getPosition().x >= 1280 || SpaceWalker.getPosition().x <= 0)
        return 1;

    if (state == 3 && _event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            currentAnimation = &AnimationUp;
            SpaceWalkermovement.y -= SpaceWalkerspeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            currentAnimation = &AnimationUp;
            SpaceWalkermovement.y += SpaceWalkerspeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentAnimation = &AnimationUp;
            SpaceWalkermovement.x += SpaceWalkerspeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentAnimation = &AnimationDown;
            SpaceWalkermovement.x -= SpaceWalkerspeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            ShooterLaser();

return 0;
}

int Render::ShooterLaser()
{
    Laser.setPosition(SpaceWalker.getPosition().x, SpaceWalker.getPosition().y);
    Lasermovement.x = Laserspeed;
}

int Render::SelectGameOver(int state)
{
    static int     choice = 1;
    
    if (_reboot == true)
        choice = 1;

    if (state == 4 && _event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choice < 2)
            choice++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choice > 1)
            choice--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return choice;

        if (choice == 1)
        {
            _aff_yes.setColor(sf::Color::Red);
            _aff_no.setColor(sf::Color::Green);
        }
        else if (choice == 2)
        {
            _aff_yes.setColor(sf::Color::Green);
            _aff_no.setColor(sf::Color::Red);
        }
return 0;
}