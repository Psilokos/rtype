/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:53:56 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-27 00:32:17
 */
 
#include "Render.hpp"

Render::Render()
{
    LoadEntity();
    SetScene();
}

int Render::LikeMusic()
{
    _sound.setLoop(true);
    _sound.play();
    return 0;
}

int Render::GameLoop()
{
    sf::RenderWindow      window(sf::VideoMode(1280, 720), "Rtype", sf::Style::Close);
    static int            State = 0;

    //LikeMusic();
    while (window.isOpen())
        {
        // update affichage Username
        _aff_username.setString(_username);

        // event Loop
        while (window.pollEvent(_event))
            {
            if (State == 0 && _event.type == sf::Event::TextEntered)
            {
                _reboot = false;
                _aff_username.setColor(sf::Color::Green);
                GetUsername(State);
            }
            if (State == 1)
                SelectServer(State);
            if (State == 2)
                SelectRoom(State);
            if (State == 3)
                Game();
            if (State == 4)
                SelectGameOver(State);

            //update state
            if (_event.type == sf::Event::KeyPressed)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    if (State == 0 && GetUsername(State) == 2)
                    {
                        _aff_username.setColor(sf::Color::Red);
                        State++;
                    }
                    else if (State == 1 && SelectServer(State) == 1)
                        State++;
                    else if (State == 2 && SelectRoom(State) == 1)
                        State++;
                    else if (State == 3 && Game() == 0)
                        State++;
                    else if (State == 4 && SelectGameOver(State) == 1)
                    {
                        State = 0;
                        _reboot = true;
                    }
                }
            //closing event
            if (_event.type == sf::Event::Closed || SelectGameOver(State) == 2)
                window.close();
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
                window.close();
            }
        if (State < 2)
        {
            window.draw(_Background);
            window.draw(_TexteZone);
            window.draw(_aff_username);
            window.draw(_aff_server1);
        }
        if (State == 2)
        {
            window.draw(_BackgroundRoom);
            window.draw(_TexteZoneRoom);
            window.draw(_aff_RoomOne);
        }
        if (State == 3)
        {
            window.draw(_BackgroundGame);
            //for aff Game map /sprite
        }
        if (State >= 4)
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