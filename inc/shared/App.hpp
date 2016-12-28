//
// App.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:17:49 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec 27 11:19:42 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

class	App
{
public:
  App(void) = default;
  App(App const &) = delete;
  App(App &&) = delete;
  ~App(void) = default;

  void	run(void) const;
};
