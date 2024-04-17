#include "Ghost_AI.h"

float manhattan_distance(Position &p1, Position &p2) {
    return (float) (std::abs(p1.getX() - p2.getX()) + std::abs(p1.getY() - p2.getY()));
}

void ghost_out_of_the_spawner(std::shared_ptr<Ghost> g, double deltatime) {
    float x, y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    if (is_in_the_right_position(x, 5)) {
        if (is_in_the_right_position(y, 8)) {
            g->setDirection(Direction::Right);
        } else if (is_in_the_right_position(y, 11)) {
            g->setDirection(Direction::Left);
        } else if ((is_in_the_right_position(y, 9)) ||
                   (is_in_the_right_position(y, 10))) {
            g->setDirection(Direction::Up);
        }
    }

    if (is_in_the_right_position(x, 3)) {
        if (is_in_the_right_position(y, 9)) {
            g->setDirection(Direction::Left);
        } else if (is_in_the_right_position(y, 10)) {
            g->setDirection(Direction::Right);
        } else if ((is_in_the_right_position(y, 6)) ||
                   (is_in_the_right_position(y, 13))) {
            g->setDirection(Direction::Down);
        }
    }

    if (((is_in_the_right_position(x, 5)) && (is_in_the_right_position(y, 6))) ||
        ((is_in_the_right_position(x, 5)) && (is_in_the_right_position(y, 13)))) {
        return;
    }

    g->tick(deltatime);
}

void ghost_manhattan_distance(std::shared_ptr<Ghost> g, std::shared_ptr<PacMan> pacman,
                              std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {

    std::vector<Direction> directions = available_directions(g, index);
    std::unordered_map<Direction, float> distances;

    // Calculate distances for each direction and store in the map
    for (const Direction& dir : directions) {
        Position supp = get_position_difference_from_direction(dir);
        Position next = {(float)g->getPosition().getX() + supp.getX(),
                         (float)g->getPosition().getY() + supp.getY()};

        Position actual_pacman_position = pacman->getPosition();

        float result = manhattan_distance(next, actual_pacman_position);
        distances[dir] = result;
    }

    auto minDistanceIterator = distances.begin();

    //scan the unordered map and find the minimum value
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        if (it->second < minDistanceIterator->second) {
            minDistanceIterator = it;
        }
    }

    Direction min_direction = minDistanceIterator->first;
    if (is_approximated_to_integer(g->getPosition().getX(), 0.1) &&
        is_approximated_to_integer(g->getPosition().getY(), 0.1))
        g->setDirection(min_direction);


    auto maxDistanceIterator = distances.begin();

    // scan the unordered map and find the maximum value
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        if (it->second > maxDistanceIterator->second) {
            maxDistanceIterator = it;
        }
    }


    //choose the minimum or the maximum manhattan distance
    if (g->get_chasing_mode()){
        //find the direction associated to the minimum value
        Direction min_direction = minDistanceIterator->first;
        if (is_approximated_to_integer(g->getPosition().getX(),0.1) &&
            is_approximated_to_integer(g->getPosition().getY(), 0.1))
            g->setDirection(min_direction);
    } else {
        //find the direction associated to the maximum value
        Direction max_direction = maxDistanceIterator->first;
        if (is_approximated_to_integer(g->getPosition().getX(),0.1) &&
            is_approximated_to_integer(g->getPosition().getY(), 0.1))
            g->setDirection(max_direction);
    }

}

void ghost_decision(std::shared_ptr<Ghost> g, std::vector<Direction> directions,
                    std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
                    std::shared_ptr<PacMan> pacman) {

    auto &random = Random::instance();
    int p = random.get_random_in_range(0,1);

    if (g->get_chasing_mode()){
        if (p == 1){
            Direction new_direction = random.get_random_direction(directions);
            g->setDirection(new_direction);
        } else {
            ghost_manhattan_distance(g, pacman, index);
        }
    } else {
        ghost_manhattan_distance(g, pacman, index);
    }
}

void ghost_AI(std::shared_ptr<Ghost> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
std::shared_ptr<PacMan> pacman) {
    std::vector<Direction> directions = available_directions(g, index);

    if (directions.size() == 1){
        g->setDirection(directions[0]);
    }


    //check if the ghost's actual position is on a corner of the map
    if (is_on_a_corner(directions.size(), g, index)){
        float x, y;

        Direction precedent = g->getDirection();
        ghost_decision(g, directions, index, pacman);
        g->setPosition(roundf(g->getPosition().getX()), roundf(g->getPosition().getY()));
        Direction actual_direction = g->getDirection();
        auto supp =  get_position_difference_from_direction(actual_direction);

        if (g->getDirection() == precedent){
            x = g->getPosition().getX();
            y = g->getPosition().getY();
            g->setPosition(x + (supp.getX() * 0.04), y + (supp.getY() * 0.04));
        }
    }

    //check if the ghost's actual position is on an intersection
    if (is_on_an_intersection(directions.size(), g)){
        float x, y;

        Direction precedent = g->getDirection();
        ghost_decision(g, directions, index, pacman);
        g->setPosition(roundf(g->getPosition().getX()), roundf(g->getPosition().getY()));
        Direction actual_direction = g->getDirection();
        auto supp =  get_position_difference_from_direction(actual_direction);

        if (g->getDirection() == precedent){
            x = g->getPosition().getX();
            y = g->getPosition().getY();
            g->setPosition(x + (supp.getX() * 0.11), y + (supp.getY() * 0.11));
        }
    }

}
