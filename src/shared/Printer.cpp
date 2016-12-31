//
// TOTPGenerator.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 23:37:09 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 02:42:55 2016 Victorien LE COUVIOUR--TUFFET
//

#include <iostream>
#include "AllAssemblies.hpp"
#include "Printer.hpp"

namespace	entity_component_system::system
{
  void
  Printer::update(database::IDataBase & db)
  {
    // recuperation de l'entity TOTP by name (du system TOTPGenerator), cas rare generalement vous utiliserez les autres getters, la jai trop peu d'entity pour avoir la necessite des autres
    Any const	totpAny = db.getEntity("TOTP");

    // si le system TOTPGenerator a deja set en DB notre entity TOTP alors la cond est vrai car trouvee lors du getEntity ci-dessus
    if (totpAny.hasValue())
      // simple getters + affichage du resultat de l'algo de totp | ici la petite difference avec le reste du programme est que je travaille directement avec l'entite runtime sans la convertir en compile time
      std::cout << totpAny.getValueByRef<entity::RTEntity>().getComponent<component::Basic<unsigned>>(::result).getAttr<::value>() << std::endl;
  }
}
