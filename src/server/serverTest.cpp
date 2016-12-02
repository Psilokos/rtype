#include <iostream>
#include <string>

#include "ASocket.hpp"
#include "WinSock.hpp"

int main(int ac, char **av) {
  network::WinSock test(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  std::string recvData, sndData;
  std::string sender, serv;
  int nb = 0;

  std::cout << test.bind("0.0.0.0", "4242") << std::endl;

  std::cout << "listening on 4242, now waiting for input" << std::endl;
  std::cout << "Connection accepted." << std::endl;

  while (1) {
    std::cout << test.recvFrom(recvData, 100, 0, sender, serv);
    std::cout << "received 6 bytes from " << sender << ":" << serv << std::endl;
    std::cout << recvData << std::endl;
    if (recvData.length() == 0)
      break;
    nb++;
    std::cout << nb << std::endl;
  }
  std::cout << "received " << nb << "/10000 packets" << std::endl;

  std::cout << "Hello, World!" << std::endl;
  while (1);
}