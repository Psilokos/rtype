#include <gtest/gtest.h>

#include <thread>
#include <cstring>
#include <unistd.h>

#include "TestConnection.hpp"
#include "Socket.hpp"
#include "Connection.hpp"

void	CoLoop(ecs::database::IDataBase &_db, int iter) {
  ecs::system::Connection	co;

  usleep(2000);
  for (int i = 0; i < iter; ++i)
    co.update(_db);
}

void	sendLoop(network::UdpSocket &cli, void *data, int size) {

  usleep(3000);
  for (int i = 0; i < 1; ++i) {
    cli.sendTo(data, size, 0, "127.0.0.1", "4242");
  }
}

TEST_F(TestConnection, SimpleConnection) {
  std::thread				Connection(CoLoop, std::ref(*_db), 1);
  std::list<ecs::entity::RTEntity>	ents;
  char					*rawReq;
  network::UdpSocket			cli;

  rawReq = new char[3 + sizeof("Helloworld")];
  *rawReq = 1;
  *reinterpret_cast<short *>(rawReq + 1) = sizeof("Helloworld");
  std::memcpy(rawReq + 3, "Helloworld", sizeof("Helloworld"));

  std::thread				send(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));

  Connection.join();
  send.join();
  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(1, ents.size());
  for (auto &ent : ents) {
    EXPECT_EQ("127.0.0.1", ent.getComponent<ecs::component::ConInfo>("ConInfo").getAttr<::ip>());
  }
}

TEST_F(TestConnection, TwoClients) {
  std::thread				Connection(CoLoop, std::ref(*_db), 2);
  std::list<ecs::entity::RTEntity>	ents;
  network::UdpSocket			clis1;
  network::UdpSocket			clis2;
  char					*rawReq;

  rawReq = new char[3 + sizeof("Helloworld")];
  *rawReq = 1;
  *reinterpret_cast<short *>(rawReq + 1) = sizeof("Helloworld");
  std::memcpy(rawReq + 3, "Helloworld", sizeof("Helloworld"));

  std::thread				cli1(sendLoop, std::ref(clis1), rawReq, 3 + sizeof("Helloworld"));
  std::thread				cli2(sendLoop, std::ref(clis2), rawReq, 3 + sizeof("Helloworld"));

  Connection.join();
  cli1.join();
  cli2.join();
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(2, ents.size());
  for (auto &ent : ents) {
    EXPECT_EQ("127.0.0.1", ent.getComponent<ecs::component::ConInfo>("ConInfo").getAttr<::ip>());
  }
}

TEST_F(TestConnection, BadRequest) {
  std::thread				Connection(CoLoop, std::ref(*_db), 1);
  std::list<ecs::entity::RTEntity>	ents;
  ecs::database::Component		*cmp;
  char					*rawReq;
  network::UdpSocket			cli;

  rawReq = new char[3 + sizeof("Helloworld")];
  *rawReq = 12;
  *reinterpret_cast<short *>(rawReq + 1) = sizeof("Helloworld");
  std::memcpy(rawReq + 3, "Helloworld", sizeof("Helloworld"));

  std::thread				send(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));

  Connection.join();
  send.join();
  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(0, ents.size());
}

TEST_F(TestConnection, UnconnectedRequest) {
  std::thread				Connection(CoLoop, std::ref(*_db), 1);
  std::list<ecs::entity::RTEntity>	ents;
  ecs::database::Component		*cmp;
  char					*rawReq;
  network::UdpSocket			cli;

  rawReq = new char[3 + sizeof("Helloworld")];
  *rawReq = 101;
  *reinterpret_cast<short *>(rawReq + 1) = sizeof("Helloworld");
  std::memcpy(rawReq + 3, "Helloworld", sizeof("Helloworld"));

  std::thread				send(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));

  Connection.join();
  send.join();
  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(0, ents.size());
}

TEST_F(TestConnection, LoginRequest) {
  std::thread				Connection(CoLoop, std::ref(*_db), 2);
  std::list<ecs::entity::RTEntity>	ents;
  ecs::database::Component		*cmp;
  char					*rawReq;
  char					resp[512];
  int					recv;
  network::UdpSocket			cli;
  std::string				ip, port;

  rawReq = new char[3 + sizeof("Helloworld")];
  *rawReq = 1;
  *reinterpret_cast<short *>(rawReq + 1) = sizeof("Helloworld");
  std::memcpy(rawReq + 3, "Helloworld", sizeof("Helloworld"));

  std::thread				send(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));
  send.join();
  std::thread				send2(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));
  send2.join();
  recv = cli.recvFrom(resp, 7, 0, ip, port);

  Connection.join();

  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  EXPECT_EQ("127.0.0.1", ip);
  EXPECT_EQ("4242", port);
  ASSERT_EQ(1, ents.size());
  ASSERT_EQ(*(int *)((ecs::system::BaseNet::request *)resp)->data, ents.front().getID());
  EXPECT_EQ("Helloworld", ents.front().getComponent<ecs::component::UserInfo>("UserInfo").getAttr<::value>());
}

TEST_F(TestConnection, DisconnectRequest) {
  std::thread				Connection(CoLoop, std::ref(*_db), 2);
  std::list<ecs::entity::RTEntity>	ents;
  ecs::database::Component		*cmp;
  char					*rawReq;
  network::UdpSocket			cli;
  std::string				ip, port;
  ecs::system::BaseNet::request		*req;


  rawReq = new char[3 + sizeof("Helloworld")];
  req = reinterpret_cast<ecs::system::BaseNet::request *>(rawReq);
  req->rc = 1;
  req->sz = sizeof("Helloworld");
  std::memcpy(req->data, "Helloworld", sizeof("Helloworld"));

  std::thread				send(sendLoop, std::ref(cli), rawReq, 3 + sizeof("Helloworld"));
  send.join();

  usleep(1000);
  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(1, ents.size());

  rawReq = new char[3];
  req = reinterpret_cast<ecs::system::BaseNet::request *>(rawReq);
  req->rc = 3;
  req->sz = 0;

  std::thread				send2(sendLoop, std::ref(cli), rawReq, 3);
  send2.join();

  usleep(1000);
  delete[] rawReq;
  ents = _db->getAllEntitiesWithComponent("ConInfo");
  ASSERT_EQ(0, ents.size());

  Connection.join();
}
