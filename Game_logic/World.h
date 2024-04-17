#ifndef PACMANV0_WORLD_H
#define PACMANV0_WORLD_H
#include "Entities/PacMan/PacMan.h"
#include "Entities/Wall/Wall.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Utils/json.hpp"
#include "../Game_representation/Concrete_factory/EntityFactory.h"
#include "Utils/Random.h"

using namespace nlohmann;

class World {
public:
    //non filtered map in input
    World(const std::string& map, unsigned int current_level);
    World() = default;

    std::vector<std::vector<std::shared_ptr<EntityModel>>> get_positional_index();
    std::vector<std::shared_ptr<EntityModel>> get_entities() const;
    std::vector<std::shared_ptr<Ghost>> get_ghosts();
    std::vector<std::shared_ptr<Fruit>> get_fruits();
    std::shared_ptr<PacMan> get_pacman();
    std::vector<std::shared_ptr<Coin>> get_coins();

    bool matrixisation(std::string& filtered_map, std::vector<std::vector<int>>& matrix);


private:

    std::vector<std::shared_ptr<EntityModel>> _entities;
    std::vector<std::vector<std::shared_ptr<EntityModel>>> _positional_index;
    std::vector<std::shared_ptr<Ghost>> _ghosts;
    std::shared_ptr<PacMan> _pacman;
    std::vector<std::shared_ptr<Fruit>> _fruits;
    std::vector<std::shared_ptr<Coin>> _coins;
};


#endif //PACMANV0_WORLD_H