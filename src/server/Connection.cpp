/*
** Connection.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 17:48:36 2016 Gabriel CADET
** Last update Sun Dec 11 22:45:55 2016 Gabriel CADET
*/

#include <iostream>

#include "Connection.hpp"

namespace ecs::system {
  Connection::Connection()
    : _sock(new network::UdpSocket())
  {
    _reqHandler[1] = &Connection::req001Handler;
    _reqHandler[101] = &Connection::req101Handler;

  }

  void		Connection::update(ecs::database::IDataBase &db) {
    int		selRet;
    char	*buf;
    if (!_respQueue.empty()) {

      if (-1 == (selRet = network::ASocket::select(std::list<network::ASocket *>(), std::list<network::ASocket *>({_sock}), std::list<network::ASocket *>(), NULL)))
        return ;
      else if (selRet)
        while (not _respQueue.empty()) {
          std::tuple<std::string, std::string, int, char *>	&resp = _respQueue.front();
          int							ret;

          ret = _sock->sendTo(std::get<3>(resp), std::get<2>(resp), 0, std::get<0>(resp), std::get<1>(resp));
          if (ret < std::get<2>(resp))
            break ;
          buf = std::get<3>(resp);
          delete[] buf;
          _respQueue.pop();
        }
    }

    if (-1 == (selRet = network::ASocket::select(std::list<network::ASocket *>({_sock}), std::list<network::ASocket *>(), std::list<network::ASocket *>(), NULL)))
      return ;
    else if (selRet) {
      rcvRequest(db);
    }
    return ;
  }

  int		Connection::rcvRequest(ecs::database::IDataBase &db) {
    int		bytes;
    std::string	ip;
    std::string	port;
    char	rcvDgram[netBufSize];
    request	*req;
    reqIter	it;

    bytes = _sock->recvFrom(rcvDgram, netBufSize, 0, ip, port);
    if (bytes < 3)
      return -1;

    req = reinterpret_cast<request *>(rcvDgram);

    if ((it = _reqHandler.find(req->rc)) != _reqHandler.end())
      return (this->*(it->second))(db, req, ip, port);

    return 0;
  }

  int		Connection::req001Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    int		eid;
    char	*respRaw;
    request	*resp;

    if (not db.getEntitiesWithComponentsValue<std::string>("ConInfo", { { "ip", ip }, { "port", port } }).empty())
      return 0;

    ecs::database::Component	*ConInfo = new ecs::database::Component({ "ip", "port" });
    ecs::database::Component	*UserName = new ecs::database::Component({ "username" });

    eid = db.addEntity();

    ConInfo->setAttr<std::string>("ip", ip);
    ConInfo->setAttr<std::string>("port", port);
    UserName->setAttr<std::string>("username", req->data);

    db.bindComponent("ConInfo", ConInfo, eid);
    db.bindComponent("UserName", UserName, eid);

    respRaw = new char[reqHeadSize + sizeof(unsigned int)];
    resp = reinterpret_cast<request *>(respRaw);
    resp->rc = 2;
    resp->sz = sizeof(unsigned int);
    *reinterpret_cast<int *>(resp->data) = eid;
    _respQueue.push({ip, port, reqHeadSize + resp->sz, respRaw});

    return 0;
  }

  int		Connection::req101Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    int		eid;
    char	*respRaw;
    request	*resp;
    std::vector<ecs::database::Entity *>	info;

    if (db.getEntitiesWithComponentsValue<std::string>("ConInfo", { { "ip", ip }, { "port", port } }).empty())
      return 0;
    //info = getRoomInfo;
    if (info.empty()) {
      char	noInfo[] = "No Room Information Available";
      respRaw = new char[reqHeadSize + sizeof(noInfo)];
      resp = reinterpret_cast<request *>(respRaw);
      resp->rc = 102;
    }


  }

} // namespace system

