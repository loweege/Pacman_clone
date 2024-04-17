#ifndef PACMANV0_GHOST_AI_H
#define PACMANV0_GHOST_AI_H

#include "../Utils/Position.h"
#include "iostream"
#include <memory>
#include "../World.h"
#include "../Utils/Utils.h"

float manhattan_distance(Position &p1, Position &p2);

void ghost_out_of_the_spawner(std::shared_ptr<Ghost> g, double deltatime);

void ghost_manhattan_distance(std::shared_ptr<Ghost> g, std::shared_ptr<PacMan> pacman,
                              std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

void ghost_decision(std::shared_ptr<Ghost> g, std::vector<Direction> directions,
                    std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
                    std::shared_ptr<PacMan> pacman);

void ghost_AI(std::shared_ptr<Ghost> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
              std::shared_ptr<PacMan> pacman);

#endif //PACMANV0_GHOST_AI_H
