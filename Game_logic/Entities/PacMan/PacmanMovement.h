#ifndef PACMANV0_PACMANMOVEMENT_H
#define PACMANV0_PACMANMOVEMENT_H

#include "../../World.h"
#include "../../Utils/Utils.h"

std::vector<Direction> available_directions_for_pacman(
        std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

void handle_wall_collision(
        std::shared_ptr<EntityModel> e, double deltatime,
        std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
        std::vector<std::shared_ptr<Fruit>> fruits);

void check_fruits(
        std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Fruit>> fruits,
        std::shared_ptr<Fruit> fruit_p);

void check_coins(
        std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Coin>> coins,
        std::shared_ptr<Coin> coin_p);

Position approxima(std::shared_ptr<PacMan> pacman);

void handle_ghost_collision(
        std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Ghost>> ghosts);

void pacman_movement(
        std::shared_ptr<PacMan> pacman, double deltatime,
        std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
        std::vector<std::shared_ptr<Fruit>> fruits,
        std::vector<std::shared_ptr<Ghost>> ghosts,
        std::vector<std::shared_ptr<Coin>> coins);

#endif //PACMANV0_PACMANMOVEMENT_H
