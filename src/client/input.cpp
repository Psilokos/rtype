/*
 * @Author: Stephane.Lejeune 
 * @Date: 2016-12-05 12:30:00 
 * @Last Modified by: Stephane.Lejeune
 * @Last Modified time: 2016-12-05 13:25:54
 */

#include "input.hpp"

Input::Input(DataBase &db): _db(db) {}

void    Input::update(void)
{
    InputLeftArrowKey();
    InputRightArrowKey();
    InputUpArrowKey();
    InputDownArrowKey();
    InputEscKey();
}

int    Input::InputLeftArrowKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        std::cout << "Key Left is Pressed" << std::endl;
        return 0;
    }
return 1;
}

int    Input::InputRightArrowKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        std::cout << "Key Right is Pressed" << std::endl;
        return 0;
    }
return 1;
}

int    Input::InputUpArrowKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        std::cout << "Key Up is Pressed" << std::endl;
        return 0;
    }
return 1;
}

int    Input::InputDownKeyArrowKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    std::cout << "Key Down is Pressed" << std::endl;
    return 0;
    }
return 1;
}

int    Input::InputEscKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    std::cout << "Key Esc is Pressed" << std::endl;
    return 0;
    }
return 1;
}


