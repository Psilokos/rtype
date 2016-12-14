/*
** Connection.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/private/
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 17:48:36 2016 Gabriel CADET
** Last update Wed Dec 14 16:30:41 2016 Gabriel CADET
*/

#include <iostream>

#include "CliConnection.hpp"

namespace ecs::system {
  Connection::Connection()
    : _sock(new network::UdpSocket()), _cliId(-1), _eid(-1), _getRoomInfo(true)
  {
    int	ret;

    _reqHandler[2] = &Connection::req002Handler;
    _reqHandler[102] = &Connection::req102Handler;
  }

  void		Connection::update(ecs::database::IDataBase &db) {
    int		selRet;
    char	*buf;
    timeval	timeout;

    if (_cliId == -1)
      if (getCliId(db) == false)
        return ;

    if (_eid == -1)
      addConnectionRequest(db);
    else if (_getRoomInfo)
      addRoomInfoRequest(db);

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
    else if (selRet)
      rcvRequest(db);
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
    if ((it = _reqHandler.find(req->rc)) != _reqHandler.end()) {
      return (this->*(it->second))(db, req, ip, port);
    }
    return 0;
  }

  bool		Connection::getCliId(ecs::database::IDataBase &db) {
    std::vector<ecs::database::Entity *>	ents;

    ents = db.getEntitiesWithComponents("User");
    if (ents.size() == 1) {
      _cliId = ents[0]->getId();
      return true;
    }
    return false;
  }

  void		Connection::addConnectionRequest(ecs::database::IDataBase &db) {
    char	*reqRaw;
    request	*req;
    std::string	ip;
    std::string	port;
    std::string	username;

    username = db.getEntityById(_cliId)->getComponent("User")->getAttr<std::string>("UserName");
    reqRaw = new char[reqHeadSize + username.length()];
    req = reinterpret_cast<request *>(reqRaw);
    req->rc = 1;
    req->sz = username.length();
    username.copy(req->data, username.length());
    getServInfo(db, ip, port);
    _respQueue.push({ ip, port, reqHeadSize + req->sz, reqRaw });
  }

  void		Connection::addRoomInfoRequest(ecs::database::IDataBase &db) {
    char	*reqRaw;
    request	*req;
    std::string	ip;
    std::string	port;
    std::string	username;

    username = db.getEntityById(_cliId)->getComponent("User")->getAttr<std::string>("UserName");
    reqRaw = new char[reqHeadSize + username.length()];
    req = reinterpret_cast<request *>(reqRaw);
    req->rc = 101;
    req->sz = username.length();
    username.copy(req->data, username.length());
    getServInfo(db, ip, port);
    _respQueue.push({ ip, port, reqHeadSize + req->sz, reqRaw });
  }

  void		getServInfo(ecs::database::IDataBase &db, std::string &ip, std::string &port) {
    std::vector<ecs::database::Entity *>	ents;
    std::string			defaultIp = "127.0.0.1";
    std::string			defaultPort = "4242";

    if ((ents = db.getEntitiesWithComponentsValue<bool>("ServInfo", { { "Selected", true } })).size() == 1) {
      ip = ents[0]->getComponent("ServInfo")->getAttr<std::string>("Ip");
      port = ents[0]->getComponent("ServInfo")->getAttr<std::string>("Port");
    }
    else {
      ip = defaultIp;
      port = defaultPort;
    }
  }

  int		Connection::req002Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    ecs::database::Component	*ServEnt = new ecs::database::Component({"id"});
    if (req->sz < sizeof(unsigned int))
      return (-1);

    _eid = *reinterpret_cast<unsigned int *>(req->data);

    ServEnt->setAttr<unsigned int>("id", _eid);
    db.bindComponent("ServEnt", ServEnt, _cliId);

    return 0;
  }

  int		Connection::req102Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    if (req->sz == 0)
      return (-1);

    return 0;
  }

  int		Connection::req104Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    std::vector<ecs::database::Entity *>	ents;

    ents = db.getEntitiesWithComponentsValue<bool>("RoomInfo", { { "Selected", true } });
    if (ents.size() != 1)
      return -1;
    ents[0]->getComponent("RoomInfo")->setAttr<std::string>("Ip", ip);
    ents[0]->getComponent("RoomInfo")->setAttr<std::string>("Port", port);
    _getRoomInfo = false;
    return 0;
  }

  void		Connection::forwardRequest(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
  }
} // namespace system

