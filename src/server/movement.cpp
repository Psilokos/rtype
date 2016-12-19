/*
** movement.cpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Tue Dec 6 15:58:53 2016 dufour_n
** Last update Tue Dec 6 15:58:53 2016 dufour_n
*/

#include <cmath>
#include "../../include/server/movement.hpp"

/** \brief Constructor of the Movement class.
 *         It simply builds a map binding each of the movement types to a method of this class.
 */
Movement::Movement() {
    this->_mvtType[NONE] = &Movement::mvtNone;
    this->_mvtType[SCROLL] = &Movement::mvtScroll;
    this->_mvtType[STRAIGHT] = &Movement::mvtStraight;
    this->_mvtType[SIN] = &Movement::mvtSin;
    this->_mvtType[MANUAL] = &Movement::mvtManual;
}


/**
 * \brief Calls the method corresponding to the movement type contained in the entity.
 */
void Movement::move(Entity &obj) {
    (this->*(_mvtType[obj["_pattern"].getAttr("namePattern")]))(obj);
}


/** \brief This method does nothing.
 *        The entity will therefore not be moved.
 */
void Movement::mvtNone(Entity &obj) const {}

/** \brief Moves the entity according to the scll speed.
 *        Mainly used for moving the background and scenery.
 */
void Movement::mvtScroll(Entity &obj) const {
    obj["_pos"].getAttr("posX") -= SCROLL_SPEED;
}

/** \brief Moves the entity along a straight line.
 */
void Movement::mvtStraight(Entity &obj) const {
    obj["_pos"].getAttr("posX") += obj["_pattern"].getAttr("vX") * obj["_speed"].getAttr("value");
    obj["_pos"].getAttr("posX") += obj["_pattern"].getAttr("vY") * obj["_speed"].getAttr("value");
}

/**
 * \brief Moves the entity along an horizontal sinusoidal path.
 *        The period and amplitude are customizable.
 */
void Movement::mvtSin(Entity &obj) const {
    float posY = obj["_pattern"].getAttr("initY");

    posY += sin(obj["_pos"].getAttr("posX") * obj["_pattern"].getAttr("freq")) * obj["_pos"].getAttr("ampl");
    obj["_pos"].getAttr("posY") = posY;
    if (obj["_pattern"].getAttr("dir"))
        obj["_pos"].getAttr("posX") += obj["_speed"].getAttr("value");
    else
        obj["_pos"].getAttr("posX") -= obj["_speed"].getAttr("value");
}
