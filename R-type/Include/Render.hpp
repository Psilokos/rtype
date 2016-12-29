/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:54:41 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-27 00:28:46
 */

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "AnimatedSprite.hpp"


class Render
{
public:
    Render();
    ~Render();
    int   LoadEntity();
    int   LikeMusic();
    int   SetScene();
    int   SetSound();
    int   SetServer();
    int   SetSceneLogin();
    int   SetSceneRoom();
    int   SetAnimate();
    int   SetSceneGameOver();
    int   GetUsername(int state);
    int   SelectServer(int state);
    int   SelectRoom(int state);
    int   Game(int state);
    int   ShooterLaser();
    int   SelectGameOver(int state);
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
    sf::Texture                   _SpaceWalkerTexture;
    sf::Texture                   _LaserTexture;
    sf::Texture                   _cible;

//SetEntity
    //Window
    sf::Vector2i                  screenDimensions;

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
    sf::Text                      _aff_RoomOne;
    int                           _idRoomOne;
    int                           _nbPlayerPerRoomOne;

    //SceneGame
    sf::Sprite                    _BackgroundGame;
    sf::Clock                     frameClock;
    sf::Time                      frameTime;
    Animation*                    currentAnimation;
    Animation*                    currentLaserAnimation;
    Animation                     AnimationUp;
    Animation                     AnimationDown;
    Animation                     LaserAnimation;
    AnimatedSprite                SpaceWalker;
    float                         SpaceWalkerspeed;
    sf::Vector2f                  SpaceWalkermovement;
// sf::FloatRect                 SpWaboundingBox;
// sf::Sprite                    SpBondSpaceWalker;
    AnimatedSprite                Laser;
    float                         Laserspeed;
    sf::Vector2f                  Lasermovement;
    sf::FloatRect                 LaserboundingBox;
    sf::Sprite                    ChampTire;

    //SceneGameOver
    sf::Sprite                    _BackgroundGameOver;
    sf::Text                      _aff_continue;
    sf::Text                      _aff_yes;
    sf::Text                      _aff_no;

//Render
    sf::Event                     _event;
    bool                          _reboot;
};


#endif /* ! RENDER_HPP_*/