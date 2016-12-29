#include <thread>

#include "client/Render.hpp"
#include "client/CliConnection.hpp"
#include "shared/IDataBase.hpp"
#include "shared/DataBase.hpp"
#include "shared/ASocket.hpp"
#include "shared/Socket.hpp"

void	RenderLoop(ecs::database::IDataBase *db) {
  ecs::system::Render launch;

  while (1) {
    launch.update(*db);
  }
}

void	ConnectionLoop(ecs::database::IDataBase *db) {
  ecs::system::Connection	con(new network::UdpSocket);

  while (1) {
    con.update(*db);
  }
}

int main(int argc, char const* argv[])
{
  ecs::database::IDataBase	*db = new ecs::database::DataBase<RTypeComponents>();
  std::thread	render(RenderLoop, db);
  std::thread	connection(ConnectionLoop, db);

  render.join();
  connection.join();
  return 0;
}
