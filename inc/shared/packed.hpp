/*
** packed.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 30 17:40:40 2016 Gabriel CADET
** Last update Fri Dec 30 17:54:39 2016 Gabriel CADET
*/

#ifndef PACKED_HPP_
#define PACKED_HPP_

#ifdef __linux__
# define PACK(__Decl__)	__Decl__ __attribute__((__packed__))
#else
# define PACK(__Decl__)	__pragma(pack(push, 1)) __Decl__ __pragma( pack(pop) )
#endif

#endif /* !PACKED_HPP_ */
