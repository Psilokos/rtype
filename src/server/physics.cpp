/*
** physics.cpp for rtype in /home/neh3mah
**
** Made by dufour_n
** Login   <dufour_n@epitech.net>
**
** Started on  Mon Nov 28 22:40:40 2016 dufour_n
** Last update Mon Nov 28 22:40:40 2016 dufour_n
*/

#include "../../include/server/physics.hpp"

Physics::Physics(DataBase &db): _db(db) {}


void    Physics::move(std::vector<Entity> &entities) {
    Movement mov = Movement();

    for (Entity obj: entities) {
        mov.move(obj);
    }
}

void    Physics::collider(Entity &obj, std::vector<Entity> &entities) {
    int objL, objR, objU, objD;
    int othL, othR, othU, othD;

    objL = obj["_pos"].getAttr("posX");
    objR = obj["_pos"].getAttr("posX") + obj["_hitbox"].getAttr("sizeX");
    objU = obj["_pos"].getAttr("posY");
    objD = obj["_pos"].getAttr("posY") + obj["_hitbox"].getAttr("sizeY");
    for (Entity other: entities) {
        othL = other["_pos"].getAttr("posX");
        othR = other["_pos"].getAttr("posX") + other["_hitbox"].getAttr("sizeX");
        othU = other["_pos"].getAttr("posY");
        othD = other["_pos"].getAttr("posY") + other["_hitbox"].getAttr("sizeY");
        if ((objL < othL && objR > othL)
                || (objL < othR && objR > othR)
                || (objU < othD && objD > othD)
                || (objU < othU && objD > othU)) {
            obj["collisionList"].getAttr("collisionList").append(other["uid"].getAttr("value"));
            other["collisionList"].getAttr("collisionList").append(obj["uid"].getAttr("value"));
        }
    }
}

void    Physics::collide(std::vector<Entity> &entities) {
    std::list<Entity>::iterator it = entities.begin();

    while (it != entities.end()) {
        if (obj["_speed"].getAttr("value")) {
            this->collider(*it, entities)
            it = entities.erase(it);
        } else
            ++it;
    }
}

void    Physics::update(void) {
    // get all components with physic_object
    STDE::any               entitiesAny = this->_db.getAllEntities(EID_PHYSIC);

    if (entitiesAny.empty())
        return;

    std::vector<Entity>  entities = STDE::any_cast<std::vector<Entity> >(entitiesAny);

    this->move(entities);
    this->collide(entities);
}
