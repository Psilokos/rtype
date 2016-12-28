//
// HMacGenerator.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:46:06 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 02:43:35 2016 Victorien LE COUVIOUR--TUFFET
//

#include <cmath>
#include <ctime>
#include <iostream>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include "HMacGenerator.hpp"

namespace	entity_component_system::system
{
  HMacGenerator::HMacGenerator(database::IDataBase & db)
  {
    std::string		msg;
    ecs::entity::HMAC	hmac; // assembly definie dans AllAssemblies.hpp

    std::cout << "enter message to encrypt: " << std::flush;
    std::cin >> msg;

    // initialization du composant key (un buffer que jalloue, et sa taille)
    // qd on set un component dans une CTEntity il faut appeler le ctor explicitement, dsl pas pu faire autrement (sinon vous pouvez aussi set les attr un a un, en plusieurs lignes)
    // le 1er arg est l'ID du component (mettre nimp ici comme on ne sait pas, set plus tard lors de la creation en DB. J'aurais bien virer ce param mais comme le component est copier son ID aussi, et si vous faite un setComponent sur une entity deja creer en DB et que vous la resauvegarder derriere ca fout le bordel)
    // les autres args sont les valeurs des attributs, dans le bon ordre evidement
    hmac.setComponent<::key>(ecs::component::DynAllocBuffer<std::uint8_t>(0, std::shared_ptr<std::uint8_t>(new std::uint8_t[msg.length()], [](std::uint8_t * ptr){ delete[] ptr; }), msg.length()));

    // copy du message dans le buffer allouee ci-dessus, je pense pas avoir grand chose a dire la, j'appelle juste std::string::copy(char *, std::size_t), qui permet de copier une string dans un buffer
    msg.copy(reinterpret_cast<char *>(hmac.getComponent<::key>().getAttr<::data>().get()), hmac.getComponent<::key>().getAttr<::size>());

    // initialization du composant result (un buffer que jalloue, et sa taille), pareil que pour le component key
    hmac.setComponent<::result>(ecs::component::DynAllocBuffer<std::uint8_t>(0, std::shared_ptr<std::uint8_t>(new std::uint8_t[64], [](std::uint8_t * ptr){ delete[] ptr; }), 64));

    // je creer une entity en DB a partir de mon assembly, l'ID est set dans l'assembly
    db.createEntityFromAssembly(hmac);

    // je set un nom en DB (optionnel, pour debug et/ou retrieve d'entity a partir de son nom, par contre si 2 entity ont le meme nom ca recuperera la 1ere donc a utiliser avec parcimonie
    // (pour le getEntity(std::string const &) je parle))
    db.setEntityName(hmac.getID(), "HMAC"); // le premier parametre est l'ID de l'entity, connu car set dans notre assembly dans l'appel ci-dessus
  }

  void
  HMacGenerator::update(database::IDataBase & db)
  {
    // recuperation de mon entity by name dans la DB, cas rare generalement vous utiliserez les autres getters, la jai trop peu d'entity pour avoir la necessite des autres,
    // je ne verifie pas que l'obj Any retourner ne soit pas vide car je pars du principe quon trouve forcement, vu que set dans le constructeur et pas senser avoir ete delete
    // getValueByRef pour eviter des alloc et free inutile (vu que notre Any contient une entity runtime, ya des allocations)
    ecs::entity::HMAC	hmac = db.getEntity("HMAC").getValueByRef<entity::RTEntity>();
    std::uint64_t	count = static_cast<std::uint64_t>(std::floor(std::time(nullptr) / 5)); // un count tte les 5 sec

    // set du count, deux manieres de set un attr
    hmac.getComponent<::count>().setAttr<::data>(reinterpret_cast<std::uint8_t *>(&count));
    hmac.getComponent<::count>().getAttr<::size>() = sizeof(std::uint64_t);

    // compute du HMAC
    _hmacSha1(hmac);

    // sauvegarde en DB
    db.setEntity(hmac);
  }

  /*
  ** private methods
  */

  void
  HMacGenerator::_hmacSha1(ecs::entity::HMAC & hmac) // rien de nouveau sur ces getters, ce sont les memes que ci-dessus
  {
    HMAC_CTX	ctx;

    ENGINE_load_builtin_engines();
    ENGINE_register_all_complete();

    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, hmac.getComponent<::key>().getAttr<::data>().get(), hmac.getComponent<::key>().getAttr<::size>(), EVP_sha1(), nullptr);
    HMAC_Update(&ctx, hmac.getComponent<::count>().getAttr<::data>(), hmac.getComponent<::count>().getAttr<::size>());
    HMAC_Final(&ctx, hmac.getComponent<::result>().getAttr<::data>().get(), &hmac.getComponent<::result>().getAttr<::size>());
    HMAC_CTX_cleanup(&ctx);
  }
}
