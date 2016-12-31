//
// RTEntity.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Mon Dec 19 14:22:22 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 19 15:12:42 2016 Victorien LE COUVIOUR--TUFFET
//

#include "RTEntity.hpp"

namespace	entity_component_system::entity
{
  RTEntity::Iterator::Iterator(decltype(RTEntity::_components)::iterator && it)			: _it(std::move(it)) {}
  RTEntity::ConstIterator::ConstIterator(decltype(RTEntity::_components)::const_iterator && it)	: _it(std::move(it)) {}

  RTEntity::Iterator &		RTEntity::Iterator::operator--(void)		{ --_it; return *this; }
  RTEntity::ConstIterator &	RTEntity::ConstIterator::operator--(void)	{ --_it; return *this; }

  RTEntity::Iterator
  RTEntity::Iterator::operator--(int)
  {
    Iterator	ret = *this;

    --_it;
    return ret;
  }

  RTEntity::ConstIterator
  RTEntity::ConstIterator::operator--(int)
  {
    ConstIterator	ret = *this;

    --_it;
    return ret;
  }

  RTEntity::Iterator &		RTEntity::Iterator::operator++(void)		{ ++_it; return *this; }
  RTEntity::ConstIterator &	RTEntity::ConstIterator::operator++(void)	{ ++_it; return *this; }

  RTEntity::Iterator
  RTEntity::Iterator::operator++(int)
  {
    RTEntity::Iterator	ret = *this;

    ++_it;
    return ret;
  }

  RTEntity::ConstIterator
  RTEntity::ConstIterator::operator++(int)
  {
    RTEntity::ConstIterator	ret = *this;

    ++_it;
    return ret;
  }

  RTEntity::Iterator::reference		RTEntity::Iterator::operator*(void)		{ return *_it; }
  RTEntity::ConstIterator::reference	RTEntity::ConstIterator::operator*(void)	{ return *_it; }

  RTEntity::Iterator::pointer		RTEntity::Iterator::operator->(void)		{ return &*_it; }
  RTEntity::ConstIterator::pointer	RTEntity::ConstIterator::operator->(void)	{ return &*_it; }

  bool	RTEntity::Iterator::operator!=(RTEntity::Iterator const & oth) const		{ return _it != oth._it; }
  bool	RTEntity::ConstIterator::operator!=(RTEntity::ConstIterator const & oth) const	{ return _it != oth._it; }

  bool	RTEntity::Iterator::operator==(RTEntity::Iterator const & oth) const		{ return _it == oth._it; }
  bool	RTEntity::ConstIterator::operator==(RTEntity::ConstIterator const & oth) const	{ return _it == oth._it; }
}
