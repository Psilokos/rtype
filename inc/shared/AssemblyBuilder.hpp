//
// AssemblyBuilder.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 15:50:20 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 18 00:53:10 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	entity_component_system
{
  namespace	database
  {
    template<typename DB>
    class	AssemblyBuilder
    {
    public:
      void	database(DB * db) { _db = db; }

      template<typename Assembly>
      void	implement(Assembly & as) { _db->createEntityFromAssembly(as); }

    private:
      DB *	_db;
    };
  }
}
