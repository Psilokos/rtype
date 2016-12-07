/*
** movement.cpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Tue Dec 6 15:58:53 2016 dufour_n
** Last update Tue Dec 6 15:58:53 2016 dufour_n
*/

#include "../../include/server/movement.hpp"

Movement::Movement() {
    this->_mvtType[STRAIGHT] = &Movement::mvtStraight;
}


void Movement::move(Entity &obj) {
    (this->*(_mvtType[obj["dirType"].getAttr("dirType")]))(obj);
}


void Movement::mvtStraight(Entity &obj) const {
    obj.pos.x -= 1 + obj.speed;
}
