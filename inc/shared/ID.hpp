//
// ID.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Thu Dec 15 23:10:02 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 03:14:37 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <ostream>

namespace	entity_component_system
{
  struct	Entity;
  struct	Component;

  //! \brief Class representing an entity / component ID in database (see its specializations below)
  template<typename> class	ID;

  //! \brief Class representing an entity ID in database
  template<>
  class	ID<Entity>
  {
  public:
    ID(void) = default;
    ID(unsigned const id) : _id(id) {}
    ID(ID<Entity> const &) = default;
    ID(ID<Entity> &&) = default;
    ~ID(void) = default;

    operator unsigned(void) const { return _id; }

    ID<Entity> &	operator=(ID<Entity> const &) = default;
    ID<Entity> &	operator=(ID<Entity> &&) = default;

    bool	operator<(ID<Entity> const & rhs) const		{ return _id < rhs._id; }
    bool	operator>(ID<Entity> const & rhs) const		{ return _id > rhs._id; }
    bool	operator<=(ID<Entity> const & rhs) const	{ return _id <= rhs._id; }
    bool	operator>=(ID<Entity> const & rhs) const	{ return _id >= rhs._id; }
    bool	operator!=(ID<Entity> const & rhs) const	{ return _id != rhs._id; }
    bool	operator==(ID<Entity> const & rhs) const	{ return _id == rhs._id; }

    friend std::ostream &	operator<<(std::ostream & os, ID<Entity> const & id) { return os << id._id << std::flush; }

  private:
    unsigned	_id;
  };

  //! \brief Class representing a component ID in database
  template<>
  class	ID<Component>
  {
  public:
    ID(void) = default;
    ID(unsigned const id) : _id(id) {}
    ID(ID<Component> const &) = default;
    ID(ID<Component> &&) = default;
    ~ID(void) = default;

    operator unsigned(void) const { return _id; }

    ID<Component> &	operator=(ID<Component> const &) = default;
    ID<Component> &	operator=(ID<Component> &&) = default;

    bool	operator<(ID<Component> const & rhs) const	{ return _id < rhs._id; }
    bool	operator>(ID<Component> const & rhs) const	{ return _id > rhs._id; }
    bool	operator<=(ID<Component> const & rhs) const	{ return _id <= rhs._id; }
    bool	operator>=(ID<Component> const & rhs) const	{ return _id >= rhs._id; }
    bool	operator!=(ID<Component> const & rhs) const	{ return _id != rhs._id; }
    bool	operator==(ID<Component> const & rhs) const	{ return _id == rhs._id; }

    friend std::ostream &	operator<<(std::ostream & os, ID<Component> const & id) { return os << id._id << std::flush; }

  private:
    unsigned	_id;
  };
}

namespace	ecs = entity_component_system;
