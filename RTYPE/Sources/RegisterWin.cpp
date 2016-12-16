#include "RegisterWin.hpp"

RegisterWin::RegisterWin()
{
    LoadEntity();
    SetEntity();
}

int RegisterWin::LikeMusic()
{
    _sound.setLoop(true);
    _sound.play();
    return 0;
}

int RegisterWin::LoadEntity()
{
    if (!_sound_buff.loadFromFile("Res/intro.ogg"))
        return EXIT_FAILURE;
    if (!_font.loadFromFile("Res/BMSPA.TTF"))
        return EXIT_FAILURE;
    if (!_background.loadFromFile("Res/BackgrondRtype.png"))
        return EXIT_FAILURE;
    if (!_login.loadFromFile("Res/transparent.png"))
        return EXIT_FAILURE;
    return 0;
}


int RegisterWin::SetEntity()
{
    _sound.setBuffer(_sound_buff);

    _Background.setTexture(_background);
    _Background.setOrigin(0, 0);
    _Background.setPosition(0, 0);

    _TexteZone.setSize(sf::Vector2f(300, 400));
    _TexteZone.setTexture(&_login);
    _TexteZone.setOutlineColor(sf::Color(32,137,154));
    _TexteZone.setOutlineThickness(3);
    _TexteZone.setOrigin(150, 0);
    _TexteZone.setPosition(640, 300);

    _aff_username.setFont(_font);
    _aff_username.setCharacterSize(20);
    _aff_username.setColor(sf::Color::Green);
    _aff_username.setPosition(510, 430);
}

int RegisterWin::GetUsername()
{
    if (_username.size() >= 13 || sf::Keyboard::isKeyPressed(sf::Keyboard::/*retourarriere*/))
        _username.erase(_username.begin());
    else
        _username += static_cast<char>(_event.text.unicode);
    std::cout << _username << std::endl;
return 0;
}

int RegisterWin::GameLoop()
{
    LikeMusic();
    sf::RenderWindow      window(sf::VideoMode(1280, 720), "Rtype - Login", sf::Style::Close);

    while (window.isOpen())
        {
        _aff_username.setString(_username);
        while (window.pollEvent(_event))
            {
            if (_event.type == sf::Event::TextEntered)
                GetUsername();
            if (_event.type == sf::Event::MouseButtonPressed)
                std::cout << "\nX :" << _event.mouseButton.x << "\nY :" << _event.mouseButton.y <<std::endl;
            if (_event.type == sf::Event::Closed)
                window.close();
            }
        window.draw(_Background);
        window.draw(_TexteZone);
        window.draw(_aff_username);
        window.display();
        window.clear(); 
        }
return 0;
}


RegisterWin::~RegisterWin(){}