/*
** Connection.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 14:47:41 2016 Gabriel CADET
** Last update Wed Dec 07 15:36:01 2016 Gabriel CADET
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "ISystem.hpp"

class Connection : public ISystem {
  public:
    Connection();
    Connection(Connection const &) = delete;
    ~Connection();

    Connection	&operator=(Connection const &) = delete;

    void	update(ecs::database::DataBase &);
};

#endif /* !CONNECTION_HPP_ */
