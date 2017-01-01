/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:54:50 
 * @Last Modified by:   Stephane.Lejeune 
 * @Last Modified time: 2016-12-26 17:54:50 
 */

#include "Render.hpp"

int Render::SetScene()
{
    SetSound();
    SetServer();
    SetSceneLogin();
    SetSceneRoom();
    SetSceneGameOver();
}

int Render::SetSound()
{
    _sound.setBuffer(_sound_buff);
}

int Render::SetServer()
{
    std::string     srv1 = "Server     -1- ";

    _aff_server1.setString(srv1);
return 0;
}

int Render::SetSceneLogin()
{
    _Background.setTexture(_background);
    _Background.setOrigin(0, 0);
    _Background.setPosition(0, 0);

    _TexteZone.setSize(sf::Vector2f(300, 400));
    _TexteZone.setTexture(&_login);
    _TexteZone.setOutlineColor(sf::Color(32,137,154));
    _TexteZone.setOutlineThickness(3);
    _TexteZone.setOrigin(150, 0);
    _TexteZone.setPosition(640, 300);

    _username = "  Username. ";
    _aff_username.setFont(_font);
    _aff_username.setCharacterSize(20);
    _aff_username.setColor(sf::Color::Green);
    _aff_username.setPosition(510, 430);

    _aff_server1.setFont(_font);
    _aff_server1.setCharacterSize(20);
    _aff_server1.setColor(sf::Color::Green);
    _aff_server1.setPosition(520, 550);
}

int Render::SetSceneRoom()
{
    _BackgroundRoom.setTexture(_backgroundRoom);
    _BackgroundRoom.setOrigin(0, 0);
    _BackgroundRoom.setPosition(0, 0);

    _TexteZoneRoom.setSize(sf::Vector2f(500, 400));
    _TexteZoneRoom.setTexture(&_loginRoom); 
    _TexteZoneRoom.setOutlineColor(sf::Color(255,255,255));
    _TexteZoneRoom.setOutlineThickness(3);
    _TexteZoneRoom.setOrigin(0, 0);
    _TexteZoneRoom.setPosition(100, 160);

    _aff_Room.setFont(_font);
    _aff_Room.setCharacterSize(20);
    _aff_Room.setString("Room");
    _aff_Room.setColor(sf::Color::Green);
    _aff_Room.setPosition(120, 285);
}

int Render::SetSceneGameOver()
{
    _BackgroundGameOver.setTexture(_backgroundGameOver);
    _BackgroundGameOver.setOrigin(0, 0);
    _BackgroundGameOver.setPosition(0, 0);

    _aff_continue.setFont(_font);
    _aff_continue.setCharacterSize(30);
    _aff_continue.setString("Continue");
    _aff_continue.setColor(sf::Color::Green);
    _aff_continue.setPosition(520, 310);

    _aff_yes.setFont(_font);
    _aff_yes.setCharacterSize(20);
    _aff_yes.setString(".Yes");
    _aff_yes.setColor(sf::Color::Green);
    _aff_yes.setPosition(520, 370);

    _aff_no.setFont(_font);
    _aff_no.setCharacterSize(20);
    _aff_no.setString(".No");
    _aff_no.setColor(sf::Color::Green);
    _aff_no.setPosition(520, 410);
}