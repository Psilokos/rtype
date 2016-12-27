#include <thread>

#include "client/Render.hpp"
#include "client/CliConnection.hpp"
#include "shared/IDataBase.hpp"
//#include "shared/DataBase.hpp"

void	RenderLoop(ecs::database::IDataBase &db) {
  Render launch;

  while (1) {
    launch.update(db);
  }
}

void	ConnectionLoop(ecs::database::IDataBase &db) {
  ecs::system::Connection	con;

  while (1) {
    con.update(db);
  }
}

int main(int argc, char const* argv[])
{
//  ecs::database::DataBase<RTypeComponents>	db;
  std::thread	render(RenderLoop, db);
  std::thread	connection(RenderLoop, db);

  render.join();
  connection.join();
  return 0;
}
