/*
** movement.hpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Tue Dec 6 15:58:58 2016 dufour_n
** Last update Tue Dec 6 15:58:58 2016 dufour_n
*/

#ifndef _MOVEMENT_HPP_
# define _MOVEMENT_HPP_

#include <map>
#include "../../include/server/mock.hpp"

#define NONE     0
#define SCROLL   1
#define STRAIGHT 2
#define SIN      3
#define MANUAL   4

class Movement {
private:
    std::map<movements, void (Movement::*)(Entity&) const>    _mvtType;

private:
    void mvtNone(Entity &obj) const;
    void mvtScroll(Entity &obj) const;
    void mvtStraight(Entity&) const;
    void mvtSin(Entity &obj) const;
    void mvtManual(Entity &obj) const;

public:
    void move(Entity&);
    Movement();
};

#endif
