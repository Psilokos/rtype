/*
** Connection.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/server
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 17:48:36 2016 Gabriel CADET
** Last update Thu Dec 29 19:14:31 2016 Gabriel CADET
*/

#include <iostream>

#include "Connection.hpp"

namespace entity_component_system::system {
  Connection::Connection()
    : _sock(new network::UdpSocket())
  {
    int	ret;

    ret = _sock->bind("0.0.0.0", "4242");
    _reqHandler[1] = &Connection::req001Handler;
    _reqHandler[3] = &Connection::req003Handler;
    _reqHandler[4] = &Connection::req004Handler;
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

  int			Connection::req001Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    char		*respRaw;
    request		*resp;
    ecs::component::ConInfo	cmp;
    std::string			username;

    cmp.setAttr<::ip>(ip);
    cmp.setAttr<::port>(port);

    if (not db.getAllEntitiesWithComponentEqualTo(database::ComponentTypeID::ConInfo, cmp).empty())
      return 0;

    username.insert(0, req->data, req->sz - 1);
    std::cout << username << std::endl;

    ecs::entity::User	newUsr;

    newUsr.getComponent<::ConInfo>().setAttr<::ip>(ip);
    newUsr.getComponent<::ConInfo>().setAttr<::port>(port);
    newUsr.getComponent<::UserInfo>().setAttr<::value>(username);

    db.createEntityFromAssembly(newUsr);

    respRaw = new char[reqHeadSize + sizeof(unsigned int)];

    resp = reinterpret_cast<request *>(respRaw);
    resp->rc = 2;
    resp->sz = sizeof(unsigned int);
    *reinterpret_cast<unsigned int *>(resp->data) = newUsr.getID();
    _respQueue.push({ip, port, reqHeadSize + resp->sz, respRaw});

    return 0;
  }

  int		Connection::req003Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    int		eid;
    char	*respRaw;
    request	*resp;
    std::list<ecs::entity::RTEntity>	info;
    ecs::component::ConInfo	cmp;

    cmp.setAttr<::ip>(ip);
    cmp.setAttr<::port>(port);

    if ((info = db.getAllEntitiesWithComponentEqualTo(database::ComponentTypeID::ConInfo, cmp)).empty())
      return 0;
    for (auto &ent : info)
      db.deleteEntity(ent.getID());
    forwardRequest(db, req, ip, port);
    respRaw = new char[reqHeadSize];
    resp = reinterpret_cast<request *>(respRaw);
    resp->rc = 5;
    resp->sz = 0;
    _respQueue.push({ ip, port, reqHeadSize + resp->sz, respRaw });
    return 0;
  }

  int		Connection::req004Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    int		eid;
    char	*respRaw;
    request	*resp;
    std::list<ecs::entity::RTEntity>	info;
    ecs::component::ConInfo	cmp;

    cmp.setAttr<::ip>(ip);
    cmp.setAttr<::port>(port);

    if ((info = db.getAllEntitiesWithComponentEqualTo(database::ComponentTypeID::ConInfo, cmp)).empty())
      return 0;

    respRaw = new char[reqHeadSize];
    resp = reinterpret_cast<request *>(respRaw);
    resp->rc = 5;
    resp->sz = 0;
    _respQueue.push({ ip, port, reqHeadSize + resp->sz, respRaw });
    return 0;
  }

  int		Connection::req101Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    int		eid;
    char	*respRaw;
    request	*resp;
    std::list<ecs::entity::RTEntity>	info;
    ecs::component::ConInfo	cmp;

    cmp.setAttr<::ip>(ip);
    cmp.setAttr<::port>(port);

    if ((info = db.getAllEntitiesWithComponentEqualTo(database::ComponentTypeID::ConInfo, cmp)).empty())
      return 0;
    //info = getRoomInfo;
    if (info.empty()) {
      respRaw = new char[reqHeadSize];
      resp = reinterpret_cast<request *>(respRaw);
      resp->rc = 102;
      resp->sz = 0;
    }
    else {
      ;
    }
    _respQueue.push({ ip, port, reqHeadSize + resp->sz, respRaw });
    return 0;
  }

  void		Connection::forwardRequest(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
  }
} // namespace system

