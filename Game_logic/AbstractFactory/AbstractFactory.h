#ifndef PACMANV0_ABSTRACTFACTORY_H
#define PACMANV0_ABSTRACTFACTORY_H
#include <memory>
#include "../../Game_logic/Entities/EntityModel.h"
#include "../../Game_logic/Entities/Ghost/Ghost.h"
#include "../../Game_logic/Entities/PacMan/PacMan.h"
#include "../../Game_logic/Entities/Collectable/Collectable.h"
#include "../../Game_logic/Entities/Wall/Wall.h"

class Factory{
    virtual std::shared_ptr<EntityModel> create_pacman(int x, int y) = 0;
    virtual std::shared_ptr<EntityModel> create_ghost(int x, int y) = 0;
    virtual std::shared_ptr<EntityModel> create_fruit(int x, int y) = 0;
    virtual std::shared_ptr<EntityModel> create_coin(int x, int y) = 0;
    virtual std::shared_ptr<EntityModel> create_wall(int x, int y) = 0;
    virtual std::shared_ptr<EntityModel> create_void_cell(int x, int y) = 0;
};


#endif //PACMANV0_ABSTRACTFACTORY_H
