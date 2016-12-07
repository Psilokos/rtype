#include <iostream>

#include "ASocket.hpp"
#include "WinSock.hpp"

int main(int ac, char **av) {
  network::WinSock test(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  std::string snd, rcv, serv, port;
  int          nb = 0;

  snd = "Salut";

  for (int i = 0; i < 10000; ++i) {
    snd = std::string("Salut") + std::to_string(i);
    std::cout << "sending \"" << snd << "\"" << std::endl;
    std::cout << test.sendTo(snd, 0, "127.0.0.1", "4242") << std::endl;
    nb++;
  }
  test.sendTo(std::string(""), 0, "127.0.0.1", "4242");

  while (1);
}