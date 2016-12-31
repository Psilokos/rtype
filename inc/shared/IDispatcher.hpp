//
// IDispatcher.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Fri Dec 16 17:47:16 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 17 16:49:16 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "CompileTime.hpp"
#include "IDispatcherPart.hpp"

template<typename> class	IDispatcher;

template<> class	IDispatcher<ct::TypesWrapper<>> {};

template<typename TItem, typename... TItems>
class	IDispatcher<ct::TypesWrapper<TItem, TItems...>> : public IDispatcherPart<TItem>, public IDispatcher<ct::TypesWrapper<TItems...>> {};
