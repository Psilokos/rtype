/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:54:03 
 * @Last Modified by:   Stephane.Lejeune 
 * @Last Modified time: 2016-12-26 17:54:03 
 */
 
#include "Render.hpp"

int Render::GetUsername()
{
    static int i = 0;

    if (_username.size() == 0 || i == 0)
    {
        _username = " ";
        i++;
    }
    else if (_username.size() >= 13 || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        _username.erase(_username.begin());
    else
        _username += static_cast<char>(_event.text.unicode);
return 0;
}

int Render::SelectServer()
{
    static int     i = 1;

    if (_event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && i < 2)
            i++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && i > 0)
            i--;

        if (i == 0)
            _aff_server1.setColor(sf::Color::Red);
        else if (i == 2)
            _aff_server1.setColor(sf::Color::Green);
return i;
}

int Render::SelectRoom()
{
    static int     i = 0;

    if (_event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && i <= 2)
            i++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && i >= 1)
            i--;

        if (i == 1)
            _aff_Room.setColor(sf::Color::Red);
        else if (i == 2)
            _aff_Room.setColor(sf::Color::Green);

return 0;
}

int Render::SelectGameOver()
{
    static int     i = 0;

    if (_event.type == sf::Event::KeyPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && i <= 2)
            i++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && i >= 1)
            i--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return i;

        if (i == 1)
        {
            _aff_yes.setColor(sf::Color::Red);
            _aff_no.setColor(sf::Color::Green);
        }
        else if (i != 1)
        {
            _aff_yes.setColor(sf::Color::Green);
            _aff_no.setColor(sf::Color::Red);
        }

return 0;
}