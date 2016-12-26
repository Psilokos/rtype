/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:53:56 
 * @Last Modified by:   Stephane.Lejeune 
 * @Last Modified time: 2016-12-26 17:53:56 
 */
 
#include "Render.hpp"

Render::Render()
{
    LoadEntity();
    SetScene();
}


int Render::GameLoop()
{
    sf::RenderWindow      window(sf::VideoMode(1280, 720), "Rtype", sf::Style::Close);
    static int            State = 0;

    while (window.isOpen())
        {
        _aff_username.setString(_username);
        while (window.pollEvent(_event))
            {
            if (_event.type == sf::Event::TextEntered && State == 0)
                GetUsername();
            else if (State == 1)
                SelectServer();
            else if (State == 3)
                SelectRoom();
            else if (State == 5)
                if (SelectGameOver() == 1)
                    window.close();
            if (_event.type == sf::Event::KeyPressed)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    _aff_username.setColor(sf::Color::Red);
                    State++;
                }
            if (_event.type == sf::Event::Closed)
                window.close();
            }
        if (State <= 2)
        {
            window.draw(_Background);
            window.draw(_TexteZone);
            window.draw(_aff_username);
            window.draw(_aff_server1);
        }
        if (State == 3)
        {
            window.draw(_BackgroundRoom);
            window.draw(_TexteZoneRoom);
            window.draw(_aff_Room);
        }
        if (State >= 4)
        {
            window.draw(_BackgroundGame);
        }
        if (State >= 5)
        {
            window.draw(_BackgroundGameOver);
            window.draw(_aff_continue);
            window.draw(_aff_yes);
            window.draw(_aff_no);
        }
    window.display();
    window.clear(); 
    }
return 0;
}

Render::~Render(){}