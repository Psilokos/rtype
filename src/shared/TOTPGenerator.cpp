//
// TOTPGenerator.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 23:37:09 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 02:38:54 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cmath>
#include "TOTPGenerator.hpp"

namespace	entity_component_system::system
{
  TOTPGenerator::TOTPGenerator(database::IDataBase & db)
  {
    entity::TOTP	totp; // assembly definie dans AllAssemblies.hpp

    // je creer une entity en DB a partir de mon assembly, l'ID est set dans l'assembly
    db.createEntityFromAssembly(totp);

    // je set un nom en DB (optionnel, pour debug et/ou retrieve d'entity a partir de son nom, par contre si 2 entity ont le meme nom ca recuperera la 1ere donc a utiliser avec parcimonie
    // (pour le getEntity(std::string const &) je parle))
    db.setEntityName(totp.getID(), "TOTP");
  }

  void
  TOTPGenerator::update(database::IDataBase & db)
  {
    // recuperation de l'entity HMAC by name (du system HMacGenerator), cas rare generalement vous utiliserez les autres getters, la jai trop peu d'entity pour avoir la necessite des autres
    Any const	hmacAny = db.getEntity("HMAC");

    if (hmacAny.hasValue()) // si le system HMacGenerator a deja set en DB notre entity HMAC alors la cond est vrai car trouvee lors du getEntity ci-dessus
      {
	// recuperation de mon entity TOTP by name dans la DB, cas rare generalement vous utiliserez les autres getters, la jai trop peu d'entity pour avoir la necessite des autres,
	// je ne verifie pas que l'obj Any retourner ne soit pas vide car je pars du principe quon trouve forcement, vu que set dans le constructeur et pas senser avoir ete delete
	// getValueByRef pour eviter des alloc et free inutile (vu que notre Any contient une entity runtime, ya des allocations)
	entity::TOTP		totp = db.getEntity("TOTP").getValueByRef<entity::RTEntity>();

	// recuperation de mon entity HMAC dans son container Any
	entity::HMAC const	hmac = hmacAny.getValueByRef<entity::RTEntity>();
	std::uint8_t		idx = hmac.getComponent<::result>().getAttr<::data>().get()[19] & 0xf; // simples getters de component / attribute

	// compute et set du resultat du TOTP avec les memes getters basiques que l'instruction precedente
	totp.getComponent<::result>().getAttr<::value>() =
	  (hmac.getComponent<::result>().getAttr<::data>().get()[idx] & 0x7f) << 24 |
	  (hmac.getComponent<::result>().getAttr<::data>().get()[idx + 1] & 0xff) << 16 |
	  (hmac.getComponent<::result>().getAttr<::data>().get()[idx + 2] & 0xff) << 8 |
	  (hmac.getComponent<::result>().getAttr<::data>().get()[idx + 3] & 0xff);

	// je tej quelques digits
	totp.getComponent<::result>().getAttr<::value>() %= static_cast<unsigned>(std::floor(std::pow(10, 6)));

	// et je sauvegarde mon entity en DB
	db.setEntity(totp);
      }
  }
}
