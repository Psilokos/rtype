/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-26 17:53:56 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-27 00:32:17
 */
 
#include "Render.hpp"

Render::Render() : SpaceWalker(sf::seconds(0.2), true, false), Laser(sf::seconds(0.2), true, false)
{
    LoadEntity();
    SetScene();
    SetAnimate();
}

int Render::LikeMusic()
{
    _sound.setLoop(true);
    _sound.play();
    return 0;
}

int Render::GameLoop()
{
    screenDimensions.x = 1280;
    screenDimensions.y = 720;
    sf::RenderWindow      window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Rtype", sf::Style::Close);
    static int            State = 0;

    LikeMusic();
    window.setFramerateLimit(60);
    while (window.isOpen())
        {
        // update affichage Username
        _aff_username.setString(_username);

        // event Loop
        while (window.pollEvent(_event))
            {
            if (State == 0 && _event.type == sf::Event::TextEntered)
                {
                    _aff_username.setColor(sf::Color::Green);
                    GetUsername(State);
                }
            if (State == 1)
                SelectServer(State);
            if (State == 2)
                SelectRoom(State);
            if (State == 3)
                Game(State);
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
                    else if (State == 4 && SelectGameOver(State) == 1)
                    {
                        _sound.stop();
                        window.close();
//                      State = 0;
//                     _reboot = true;
                    }
                }

            if (State == 3 && Game(State) == 1)
                State++;

            //closing event
            if (_event.type == sf::Event::Closed || SelectGameOver(State) == 2)
                window.close();
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
                window.close();
            }

//CollisioN
/*
            SpWaboundingBox = SpBondSpaceWalker.getGlobalBounds();
            LaserboundingBox = ChampTire.getGlobalBounds();
            std::cout << "ct      X: " << ChampTire.getPosition().x << "  Y: " << ChampTire.getPosition().y << std::endl;
            std::cout << "sp      X: " << SpaceWalker.getPosition().x << "  Y: " << SpaceWalker.getPosition().y << std::endl;
            std::cout << "spBound X: " << SpBondSpaceWalker.getPosition().x << "  Y: " << SpBondSpaceWalker.getPosition().y << std::endl;
        if (SpWaboundingBox.intersects(LaserboundingBox))
            std::cout << " Bound SpWa touché------------------------------------------" << std::endl;
*/
//CollisioN 

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
            frameTime = frameClock.restart();
            SpBondSpaceWalker.setPosition(SpaceWalker.getPosition().x, SpaceWalker.getPosition().y);
            SpaceWalker.play(*currentAnimation);
            SpaceWalker.move(SpaceWalkermovement * frameTime.asSeconds());
            SpaceWalker.update(frameTime);

            Laser.play(*currentLaserAnimation);
            Laser.move(Lasermovement * frameTime.asSeconds());
            Laser.update(frameTime);

            window.draw(_BackgroundGame);
            window.draw(ChampTire); // test collision "le truck bleu"
            window.draw(SpaceWalker);
            window.draw(Laser);
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