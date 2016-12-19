//
// IDispatcherPart.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 16:49:32 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 16:49:53 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

template<typename TItem>
class	IDispatcherPart
{
public:
  virtual void	dispatch(TItem & item) = 0;
};
