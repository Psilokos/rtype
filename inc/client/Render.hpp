/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:54:41 
 * @Last Modified by:   Stephane.Lejeune 
 * @Last Modified time: 2016-12-26 17:54:41 
 */

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Render
{
public:
    Render();
    ~Render();
    int   LoadEntity();
    int   SetScene();
    int   SetSound();
    int   SetServer();
    int   SetSceneLogin();
    int   SetSceneRoom();
    int   SetSceneGameOver();
    int   GetUsername();
    int   SelectServer();
    int   SelectRoom();
    int   SelectGameOver();
    int   GameLoop();
public:


//LoadEntity
    sf::SoundBuffer               _sound_buff;
    sf::Font                      _font;
    sf::Texture                   _background;
    sf::Texture                   _backgroundRoom;
    sf::Texture                   _backgroundGame;
    sf::Texture                   _backgroundGameOver;
    sf::Texture                   _login;
    sf::Texture                   _loginRoom;

//SetEntity

    //Sound
    sf::Sound                     _sound;

    //SceneLogin
    sf::Sprite                    _Background;
    sf::RectangleShape            _TexteZone;
    std::string                   _username;
    sf::Text                      _aff_username;
    sf::Text                      _aff_server1;

    //SceneRoom
    sf::Sprite                    _BackgroundRoom;
    sf::RectangleShape            _TexteZoneRoom;
    sf::Text                      _aff_Room;

    //SceneGame
    sf::Sprite                    _BackgroundGame;

    //SceneGameOver
    sf::Sprite                    _BackgroundGameOver;
    sf::Text                      _aff_continue;
    sf::Text                      _aff_yes;
    sf::Text                      _aff_no;

//Render
    sf::Event                     _event;
};


#endif /* ! RENDER_HPP_*/