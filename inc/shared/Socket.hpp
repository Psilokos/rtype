/*
** Socket.hpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/inc/shared
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Fri Dec 02 19:35:21 2016 Gabriel CADET
** Last update Fri Dec 02 19:36:13 2016 Gabriel CADET
*/

#ifdef __linux__
# include "UnixSock.hpp"
#else
# include "WinSock.hpp"
#endif
