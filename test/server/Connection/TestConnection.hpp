/*
** TestConnection.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/test/server/Connection
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Mon Dec 12 16:24:00 2016 Gabriel CADET
** Last update Thu Dec 29 18:40:07 2016 Gabriel CADET
*/

#ifndef TESTCONNECTION_HPP_
#define TESTCONNECTION_HPP_

#include "IDataBase.hpp"
#include "DataBase.hpp"

class TestConnection : public ::testing::Test {
  protected:
    virtual void SetUp() {
      _db = new ecs::database::DataBase<RTypeComponents>();
    }

    virtual void TearDown() {
      delete _db;
    }

    ecs::database::IDataBase	*_db;
};
#endif /* !TESTCONNECTION_HPP_ */
