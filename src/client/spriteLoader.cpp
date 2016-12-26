/*
** spriteLoader.cpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Wed Dec 14 17:41:31 2016 dufour_n
** Last update Wed Dec 14 17:41:31 2016 dufour_n
*/

#include <string>
#include <cstddef>
#include <fstream>
#include "../../include/client/spriteLoader.hpp"


SpriteLoader::SpriteLoader() {}

// id|fname|x|y|sx|sy

bool isNum(std::string &s) {
    int i = 0;

    while (s[i]) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    if (!i)
        return false;
    return true;
}

int toInt(const std::string &s) {
    return (std::stoi(s, NULL, 10));
}

void    SpriteLoader::parseLine(std::string &line, std::vector<std::string> &contents) {
    size_t  beg, end;
    int     i = 2;

    end = 0;
    while (end != std::string::npos) {
        beg = end;
        end = line.find('|', beg);
        if (end != std::string::npos)
            contents.push_back(line.substr(beg, end - beg));
        else
            contents.push_back(line.substr(beg, line.length()));
    }

    if (!contents.size() < 2
            || !isNum(contents[0])
            || !contents[1].length())
        contents.clear();
    while (i < contents.size()) {
        if (!isNum(contents[i])) {
            contents.clear();
            return;
        }
        ++i;
    }
}

void    SpriteLoader::getSprite(std::string &line, std::vector<std::string> &c) {
    sf::Texture tex;
    bool        flag = false;

    this->parseLine(line, c);
    if (c.size() == 6)
        flag = tex.loadFromFile(c[1], sf::IntRect(toInt(c[2]), toInt(c[3]), toInt(c[4]), toInt(c[5])));
    else if (c.size() == 2)
        flag = tex.loadFromFile(c[1]);

    if (flag)
        this->_sprites[(SPRITE_TYPE)toInt(c[0])] = tex;
    c.clear();
}

void    SpriteLoader::readFile(std::string &fname) {
    std::vector<std::string>    contents;
    std::ifstream               file(fname.c_str());
    std::string                 line;

    if (!file.is_open())
        return;

    while (std::getline(file, line)) {
        if (line[0] != '#')
            this->getSprite(line, contents);
    }
}

bool            SpriteLoader::hasSprite(SPRITE_TYPE arg) const {
    return (this->_sprites.find(arg) != this->_sprites.end());
}

sf::Texture     &SpriteLoader::operator[](SPRITE_TYPE arg) {
    return (this->_sprites[arg]);
}
