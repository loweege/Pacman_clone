#include "EntityFactory.h"
#include "../Entities/Ghost/Ghost_v.h"
#include "../Entities/PacMan/PacMan_v.h"
#include "../Entities/Collectale/Collectable_v.h"
#include "../Entities/Wall/Wall_v.h"
#include "../Entities/VoidCell/VoidCell_v.h"



std::shared_ptr<EntityModel> EntityFactory::create_ghost(int x, int y){
    auto ghost_model = std::make_shared<Ghost>();
    auto ghost_view = std::make_shared<Ghost_v>(ghost_model);
    ghost_model->attach(ghost_view);
    return ghost_model;
}

std::shared_ptr<EntityModel> EntityFactory::create_pacman(int x, int y){
    auto pacman_model = std::make_shared<PacMan>();
    auto pacman_view = std::make_shared<PacMan_v>(pacman_model);
    pacman_model->attach(pacman_view);
    return pacman_model;
}

std::shared_ptr<EntityModel> EntityFactory::create_fruit(int x, int y){
    auto fruit_model = std::make_shared<Fruit>();
    auto fruit_view = std::make_shared<Collectable_v>(fruit_model);
    fruit_model->attach(fruit_view);
    return fruit_model;
}

std::shared_ptr<EntityModel> EntityFactory::create_coin(int x, int y){
    auto coin_model = std::make_shared<Coin>();
    auto coin_view = std::make_shared<Collectable_v>(coin_model);
    coin_model->attach(coin_view);
    return coin_model;
}

std::shared_ptr<EntityModel> EntityFactory::create_wall(int x, int y){
    auto wall_model = std::make_shared<Wall>();
    auto wall_view = std::make_shared<Wall_v>(wall_model);
    wall_model->attach(wall_view);
    return wall_model;
}

std::shared_ptr<EntityModel> EntityFactory::create_void_cell(int x, int y) {
    auto void_cell_model = std::make_shared<VoidCell>();
    auto void_cell_view = std::make_shared<VoidCell_v>(void_cell_model);
    void_cell_model->attach(void_cell_view);
    return void_cell_model;
}