#ifndef REGISTERWIN_HPP_
#define REGISTERWIN_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class RegisterWin
{
public:
    RegisterWin();
    ~RegisterWin();
    int   LikeMusic();
    int   LoadEntity();
    int   SetEntity();
    int   GetUsername();
    int   GameLoop();
public:
    sf::Font                      _font;
    sf::Texture                   _background;
    sf::Texture                   _login;
    sf::Sprite                    _Background;
    sf::SoundBuffer               _sound_buff;
    sf::Sound                     _sound;
    sf::Event                     _event;
    sf::Text                      _aff_username;
    sf::RectangleShape            _TexteZone;
    std::string                   _username;
};


#endif /* ! REGISTERWIN_HPP_*/