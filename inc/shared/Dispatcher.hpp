//
// Dispatcher.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec 16 17:52:20 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 17:00:59 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "IDispatcher.hpp"

template<typename, typename, typename> class	Dispatcher;

template<typename IDsp, typename TMixedImpl> class	Dispatcher<ct::TypesWrapper<>, IDsp, TMixedImpl> : public IDsp, public TMixedImpl {};

template<typename TItem, typename... TItems, typename IDsp, typename TMixedImpl>
class	Dispatcher<ct::TypesWrapper<TItem, TItems...>, IDsp, TMixedImpl> : public Dispatcher<ct::TypesWrapper<TItems...>, IDsp, TMixedImpl>
{
public:
  virtual void	dispatch(TItem & item) { this->implement(item); }
};
