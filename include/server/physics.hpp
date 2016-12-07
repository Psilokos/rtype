/*
** physics.hpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Mon Nov 28 22:40:36 2016 dufour_n
** Last update Mon Nov 28 22:40:36 2016 dufour_n
*/

#ifndef _PHYSICS_HPP
#define _PHYSICS_HPP_

#include "../../include/server/mock.hpp"
#include "../../include/server/movement.hpp"

#include <map>
#include <experimental/any>
#include <vector>
#include <utility>


# define STDE std::experimental


class Physics {
private:
    DataBase            &_db;

private:
    void                mvtScroll(Entity &);

    void                move(std::vector<Entity> &);
    void                updateDir(Entity &);
    void    collide(std::vector<Entity> &entities);
    void    collider(Entity &obj, std::vector<Entity> &entities);


public:
    Physics(DataBase &);
    void    update(void);
};

#endif /* !_PHYSICS_HPP_ */
