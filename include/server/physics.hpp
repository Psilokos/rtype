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

class DataBase {};

class Physics {
private:
    DataBase    &_db;

public:
    Physics(DataBase &);
    void    update(void);
};

#endif /* !_PHYSICS_HPP_ */
