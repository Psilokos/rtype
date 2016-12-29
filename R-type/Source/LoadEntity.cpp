#include "Render.hpp"

int Render::LoadEntity()
{
    if (!_sound_buff.loadFromFile("Res/intro.ogg"))
        return EXIT_FAILURE;
    if (!_font.loadFromFile("Res/BMSPA.TTF"))
        return EXIT_FAILURE;
    if (!_background.loadFromFile("Res/BackgrondRtype.png"))
        return EXIT_FAILURE;
    if (!_backgroundRoom.loadFromFile("Res/pioneerplaque.png"))
        return EXIT_FAILURE;
    if (!_backgroundGame.loadFromFile("Res/lejeu.png"))
        return EXIT_FAILURE;
    if (!_backgroundGameOver.loadFromFile("Res/Gameover.png"))
        return EXIT_FAILURE;
    if (!_login.loadFromFile("Res/transparent.png"))
        return EXIT_FAILURE;
    if (!_loginRoom.loadFromFile("Res/Roomselect.png"))
        return EXIT_FAILURE;
    if (!_SpaceWalkerTexture.loadFromFile("Res/vaisseau.png"))
        return EXIT_FAILURE;
    if (!_LaserTexture.loadFromFile("Res/laser.png"))
        return EXIT_FAILURE;
    if (!_cible.loadFromFile("Res/r-typesheet30a.gif"))
        return EXIT_FAILURE;
    return 0;
}