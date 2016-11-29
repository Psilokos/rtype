/*
** NetErrors.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Tue Nov 29 14:31:28 2016 Gabriel CADET
** Last update Tue Nov 29 14:36:19 2016 Gabriel CADET
*/

#ifndef NETERRORS_HPP_
#define NETERRORS_HPP_

#include <exception>

class Network : public std::exception {
  const char*	what() const noexcept { return "A Network Operation failed.\n"; }
};

#endif /* !NETERRORS_HPP_ */
