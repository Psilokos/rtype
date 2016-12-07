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


class Movement {
private:
    std::map<movements, void (Movement::*)(Entity&) const>    _mvtType;

private:
    void mvtStraight(Entity&) const;

public:
    void move(Entity&);
    Movement();
};

#endif
