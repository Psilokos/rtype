/*
** Connection.cpp for rtype in /home/phantomas/Project/Tek3/Advanced_CPP/rtype/src/private/
**
** Made by Gabriel CADET
** Login   <gabriel.cadet@epitech.eu>
**
** Started on  Wed Dec 07 17:48:36 2016 Gabriel CADET
** Last update Sat Dec 31 20:00:38 2016 Gabriel CADET
*/

#include <iostream>

#include "CliConnection.hpp"

namespace entity_component_system::system {
  Connection::Connection(network::UdpSocket *sock)
    : _sock(sock), _cliId(UINT_MAX), _eid(UINT_MAX), _roomId(UINT_MAX), _getRoomInfo(true)
  {
    int	ret;

    _reqHandler[2] = &Connection::req002Handler;
    _reqHandler[5] = &Connection::req005Handler;
    _reqHandler[102] = &Connection::req102Handler;
    _reqHandler[104] = &Connection::req104Handler;
    _reqHandler[105] = &Connection::req105Handler;
  }

  void		Connection::update(ecs::database::IDataBase &db) {
    int		selRet;
    char	*buf;
    timeval	timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    if (UINT_MAX == _cliId)
      if (getCliId(db) == false)
        return ;

    if (UINT_MAX == _eid)
      addConnectionRequest(db);
    else if (_getRoomInfo)
      addRoomInfoRequest(db);

    getPendingAction(db);

    if (!_respQueue.empty()) {
      if (-1 == (selRet = network::ASocket::select(std::list<network::ASocket *>(), std::list<network::ASocket *>({_sock}), std::list<network::ASocket *>(), NULL)))
        return ;
      else if (selRet) {
        while (not _respQueue.empty()) {
          response_t	&resp = _respQueue.front();
          int		ret;

          ret = _sock->sendTo(std::get<3>(resp), std::get<2>(resp), 0, std::get<0>(resp), std::get<1>(resp));
          if (ret < std::get<2>(resp))
            ; //error handling of retry ?

          delete[] std::get<3>(resp);
        }
      }
    }

    if (-1 == (selRet = network::ASocket::select(std::list<network::ASocket *>({_sock}), std::list<network::ASocket *>(), std::list<network::ASocket *>(), &timeout)))
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

  bool					Connection::getCliId(ecs::database::IDataBase &db) {
    std::list<ecs::entity::RTEntity>	ents;

    ents = db.getAllEntitiesWithComponent("User");
    if (ents.size() == 1) {
      _cliId = ents.front().getID();
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

    username = db.getEntity(_cliId).getValueByRef<entity::RTEntity>().getComponent<ecs::component::UserInfo>("UserInfo").getAttr<::value>();
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

    reqRaw = new char[reqHeadSize];
    req = reinterpret_cast<request *>(reqRaw);
    req->rc = 101;
    getServInfo(db, ip, port);
    _respQueue.push({ ip, port, reqHeadSize + req->sz, reqRaw });
  }

  void						Connection::getServInfo(ecs::database::IDataBase &db, std::string &ip, std::string &port) {
    std::list<entity::RTEntity>			ents;
    std::string					defaultIp = "127.0.0.1";
    std::string					defaultPort = "4242";

    if ((ents = db.getAllEntitiesWithComponentEqualTo(database::ComponentTypeID::ServSelected, component::ServSelected(0, true))).size() != 0) {
      ip = ents.front().getComponent<component::ConInfo>("ConInfo").getAttr<::ip>();
      port = ents.front().getComponent<component::ConInfo>("ConInfo").getAttr<::port>();
    }
    else {
      ip = defaultIp;
      port = defaultPort;
    }
  }

  int		Connection::req002Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    if (req->sz < sizeof(unsigned int))
      return (-1);

    _eid = *reinterpret_cast<unsigned int *>(req->data);

    BaseNet::_relation_id[_eid] = _cliId;
    return 0;
  }

  int		Connection::req005Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    auto	it = _pending.begin();

    if ((it = std::find_if(it, _pending.end(), [](pendingAction &act){ return std::get<1>(act) == DISCONNECT; })) != _pending.end())
      _pending.erase(it);

    return 0;
  }

  int		Connection::req102Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    BaseNet::dbInfo	*cmp;
    entity::Room	room;
    std::shared_ptr<component::RoomInfo>	inf;

    if (req->sz == 0)
      return (-1);

    cmp = reinterpret_cast<dbInfo *>(req->data);
    inf = component::RoomInfo::deserialize(req->data, req->sz);

    if (_relation_id.find(cmp->eid) == _relation_id.end()) {
      room.setComponent<::RoomInfo>(*inf);
      db.createEntityFromAssembly(room);
      BaseNet::_relation_id[cmp->eid] = room.getID();
    }
    else {
      auto relation = _relation_id.find(cmp->eid);
      room = db.getEntity(relation->second).getValueByRef<entity::RTEntity>();
      room.setComponent<::RoomInfo>(*inf);
      db.setEntity(room);
    }

    return 0;
  }

  int			Connection::req104Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    entity::RTEntity	ent;
    BaseNet::dbInfo	*tmp;
    std::shared_ptr<component::ConInfo>	inf;
    std::string				srvPort;
    auto		it = _pending.begin();

    if (UINT_MAX == _roomId)
      return 0;

    ent = db.getEntity(_roomId).getValueByRef<entity::RTEntity>();

    tmp = reinterpret_cast<dbInfo *>(req->data);
    inf = component::ConInfo::deserialize(req->data, req->sz);
    if (inf->getAttr<::ip>() == "0.0.0.0")
      getServInfo(db, inf->getAttr<::ip>(), srvPort);
    ent.addComponent(std::string(::ConInfo), *inf);
    db.setEntity(ent);
    _getRoomInfo = false;

    if ((it = std::find_if(_pending.begin(), _pending.end(), [](pendingAction &act){ return std::get<1>(act) == BaseNet::CONNECT; })) != _pending.end())
      _pending.erase(it);

    return 0;
  }

  int		Connection::req105Handler(ecs::database::IDataBase &db, request *req, std::string const &ip, std::string const &port) {
    auto	it = _pending.begin();

    if ((it = std::find_if(_pending.begin(), _pending.end(), [](pendingAction &act){ return std::get<1>(act) == BaseNet::CONNECT; })) != _pending.end())
      _pending.erase(it);

    return 0;
  }

  void		Connection::getPendingAction(ecs::database::IDataBase &db) {
    std::string	ip;
    std::string	port;
    request*	resp;
    char	*respRaw;

    getNetAction(BaseNet::CONNECTION, _pending);

    if (not _pending.empty())
      getServInfo(db, ip, port);

    for (pendingAction act : _pending) {
      switch (std::get<1>(act)) {
        case DISCONNECT:
          respRaw = new char[reqHeadSize];

          resp = reinterpret_cast<request *>(respRaw);
          resp->rc = 3;
          resp->sz = 0;

          _respQueue.push({ip, port, reqHeadSize + resp->sz, respRaw});
          break;
        case CONNECT:
          respRaw = new char[reqHeadSize + sizeof(int)];

          resp = reinterpret_cast<request *>(respRaw);
          resp->rc = 103;
          resp->sz = 4;
          *reinterpret_cast<unsigned *>(resp->data) = *reinterpret_cast<unsigned *>(std::get<2>(act));
          _roomId = *reinterpret_cast<unsigned *>(resp->data);

          _respQueue.push({ip, port, reqHeadSize + resp->sz, respRaw});
          delete[] std::get<2>(act);
          break;
        default:
          break;
      }
    }
  }
} // namespace system

