#ifndef PACMANV0_ENTITYFACTORY_H
#define PACMANV0_ENTITYFACTORY_H
#include "../../Game_logic/AbstractFactory/AbstractFactory.h"


class EntityFactory : public Factory {
public:
    virtual std::shared_ptr<EntityModel> create_pacman(int x, int y);
    virtual std::shared_ptr<EntityModel> create_ghost(int x, int y);
    virtual std::shared_ptr<EntityModel> create_fruit(int x, int y);
    virtual std::shared_ptr<EntityModel> create_coin(int x, int y);
    virtual std::shared_ptr<EntityModel> create_wall(int x, int y);
    virtual std::shared_ptr<EntityModel> create_void_cell(int x, int y);
};

#endif //PACMANV0_ENTITYFACTORY_H