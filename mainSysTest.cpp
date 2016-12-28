//
// mainSysTest.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 19:10:15 2016 Victorien LE COUVIOUR--TUFFET
// Last update Tue Dec 27 23:12:20 2016 Victorien LE COUVIOUR--TUFFET
//

#include <iostream>
#include "Any.hpp"
#include "App.hpp"

int	main(void)
{
  App	app;

  try
    {
      app.run();
    }
  catch (Any::BadType const & e)
    {
      std::cerr << "FATAL ERROR: " << e.what() << std::endl;
    }
  return 0;
}
