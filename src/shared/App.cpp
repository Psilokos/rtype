//
// App.cpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Tue Dec 27 11:18:27 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 28 02:47:08 2016 Victorien LE COUVIOUR--TUFFET
//

#include <chrono>
#include <thread>
#include "App.hpp"
#include "DataBase.hpp"
#include "HMacGenerator.hpp"
#include "Printer.hpp"
#include "TOTPGenerator.hpp"

void
App::run(void) const
{
  // la DB, ctor par defaut, RTypeComponents -> AllComponents.hpp (c un typedef de tous les components du jeu)
  ecs::database::DataBase<RTypeComponents>	db;

  // le system de generation d'HMAC, on lui passe la db pour quil puisse creer ses entities
  ecs::system::HMacGenerator	hmacGen(db);

  // le system de generation de TOTP (1 tte les 5 sec), on lui passe la db pour quil puisse creer ses entities
  ecs::system::TOTPGenerator	totpGen(db);

  // entry point des threads de calcul
  std::function<void(ecs::system::ISystem &, ecs::database::IDataBase &)>	lambda = [](ecs::system::ISystem & sys, ecs::database::IDataBase & db){ while (1) sys.update(db); }; // update du system

  // pas grand chose a dire, je lance simplement mes threads de calcul (ils tournent vite comme des batards, ca montre quil ny a pas de probleme dacces concurrentiel)
  std::thread	th[2] = { std::thread(lambda, std::ref(hmacGen), std::ref(db)), std::thread(lambda, std::ref(totpGen), std::ref(db)) };

  // thread d'affichage
  std::thread	dispTh([](ecs::database::IDataBase & db) // entry point du thread
		       {
			 ecs::system::Printer	printer; // system d'affichage

			 while (1)
			   {
			     // mesure du temps avant update
			     auto	start = std::chrono::system_clock::now();

			     // update du system
			     printer.update(db);

			     // attente afin d'afficher un resultat par seconde, ni +, ni -
			     std::this_thread::sleep_for(std::chrono::duration<double>(1) - (std::chrono::system_clock::now() - start));
			   }
		       }, std::ref(db));

  dispTh.join(); // attente de fin (jamais, faut envoyer un signal d'arret, genre ctrl-c, oui c crade, mais.... jmen bats la race c pour l'exemple)
}
