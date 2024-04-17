#include "World.h"
#include "Utils/Stopwatch.h"


std::vector<std::vector<std::shared_ptr<EntityModel>>> World::get_positional_index() {
    return _positional_index;
}

std::vector<std::shared_ptr<Ghost>> World::get_ghosts() {
    return _ghosts;
}

std::vector<std::shared_ptr<EntityModel>> World::get_entities() const {
    return _entities;
}

std::shared_ptr<PacMan> World::get_pacman() {
    return _pacman;
}

std::vector<std::shared_ptr<Fruit>> World::get_fruits() {
    return _fruits;
}

std::vector<std::shared_ptr<Coin>> World::get_coins() {
    return _coins;
}




bool World::matrixisation(std::string &filtered_map, std::vector<std::vector<int>>& matrix) {

    json jsonArray = json::parse("[" + filtered_map + "]");

    if (jsonArray.is_array()) {
        // Create a 2D vector to store the matrix

        // Iterate through each array in the outer array
        for (const auto& rowArray : jsonArray) {
            // Check if the inner array is also an array
            if (rowArray.is_array()) {
                // Create a vector to store the current row
                std::vector<int> row;

                // Iterate through each element in the inner array
                for (const auto& element : rowArray) {
                    // Assuming the matrix elements are integers
                    row.push_back(element.get<int>());
                }

                // Add the current row to the matrix
                matrix.push_back(row);
            } else {
                std::cerr << "Invalid format for inner array!" << std::endl;
                return false; // Return an error code
            }
        }

    } else {
        std::cerr << "Invalid format for outer array!" << std::endl;
        return false; // Return an error code
    }
    return false;
}

World::World(const std::string& string_map, unsigned int current_level){

    // Read the JSON file into a string
    std::string filtered_string_map = string_map.substr(8,string_map.size() - 10);

    std::vector<std::vector<int>> matrix(0, std::vector<int>(20, 0));
    matrixisation(filtered_string_map, matrix);

    EntityFactory factory;

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t z = 0; z < matrix[i].size(); ++z) {


            if (matrix[i][z] == 1){
                auto entity = factory.create_pacman(i, z);
                if (entity){
                    entity->setPosition(i,z);

                    _entities.push_back(entity);

                    std::shared_ptr<PacMan> pacman = std::dynamic_pointer_cast<PacMan>(entity);
                    pacman->setSpeed(3);
                    _pacman = pacman;
                }
            }

            if (matrix[i][z] == 2){
                auto entity = factory.create_coin(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);

                    std::shared_ptr<Coin> coin = std::dynamic_pointer_cast<Coin>(entity);
                    _coins.push_back(coin);
                }
            }

            if (matrix[i][z] == 3){
                auto entity = factory.create_ghost(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);

                    std::shared_ptr<Ghost> ghost = std::dynamic_pointer_cast<Ghost>(entity);
                    ghost->setSpeed(2 + current_level*0.2);
                    _ghosts.push_back(ghost);
                }
            }

            if (matrix[i][z] == 4){
                auto entity = factory.create_fruit(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                    std::shared_ptr<Fruit> f = std::dynamic_pointer_cast<Fruit>(entity);
                    _fruits.push_back(f);
                }
            }

            if (matrix[i][z] == 5){
                auto entity = factory.create_wall(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                }
            }

            if (matrix[i][z] == 6){
                auto entity = factory.create_void_cell(i,z);
                if (entity){
                    entity->setPosition(i,z);
                    _entities.push_back(entity);
                }
            }

        }
    }



    //here you create the positional index matrix
    std::vector<std::vector<std::shared_ptr<EntityModel>>> positional_index(
            matrix.size(), std::vector<std::shared_ptr<EntityModel>>(matrix[0].size(), nullptr));

    // Populate the positional index matrix with entities
    for (const auto& entity : _entities) {
        auto row = entity->getPosition().getX();
        auto col = entity->getPosition().getY();
        positional_index[row][col] = entity;
    }

    _positional_index = positional_index;
}









