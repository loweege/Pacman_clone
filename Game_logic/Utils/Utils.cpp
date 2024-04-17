#include "Utils.h"

#include "Utils.h"

bool is_in_the_right_position(float n, float m) {
    float error = 0.05;
    if ((n > m - error) && (n < m + error)){
        return true;
    } else {
        return false;
    }
}

bool is_approximated_to_integer(float number, float tolerance) {
    // Round the number to the decimal place
    double roundedNumber = roundf(number * 10.0) / 10.0;
    //float tolerance = 0.01;

    // Check if the rounded number is within the specified tolerance of an integer
    if (fabs(roundedNumber - roundf(roundedNumber)) <= tolerance) {
        return true;
    } else {
        return false;
    }
}

bool is_on_an_intersection(int directions_size, std::shared_ptr<EntityModel> g) {
    float x,y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    if ( (directions_size >= 3) &&
         (is_approximated_to_integer(x, 0.06)) &&
         (is_approximated_to_integer(y, 0.06)) ){
        return true;
    }

    return false;
}

Direction get_direction_from_position(const Position& diff) {
    if (diff.getX() == -1) return Direction::Up;
    if (diff.getX() == 1) return Direction::Down;
    if (diff.getY() == -1) return Direction::Left;
    if (diff.getY() == 1) return Direction::Right;

    return Direction::None;
}

Position get_position_difference_from_direction(Direction dir) {
    switch (dir) {
        case Direction::Left:
            return { 0, -1 };
        case Direction::Right:
            return { 0, +1 };
        case Direction::Up:
            return { -1, 0 };
        case Direction::Down:
            return { +1, 0 };
        default:
            return { 0, 0 };
    }
}

std::vector<Direction> available_directions(std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {
    std::vector<Position> adjancent_positions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    std::vector<Direction> directions;


    // Use iterator to remove directions that satisfy the condition
    adjancent_positions.erase(
            std::remove_if(
                    adjancent_positions.begin(),
                    adjancent_positions.end(),
                    [&](const Position& pos) {
                        Position nextPosition =
                                {roundf(g->getPosition().getX() + pos.getX()),
                                 roundf(g->getPosition().getY() + pos.getY())};
                        std::shared_ptr<EntityModel> neighbor =
                                index[nextPosition.getX()][nextPosition.getY()];
                        return (neighbor->getType() == 5);
                    }),
            adjancent_positions.end());

    //here I need to translate the positions into the adjacent_position vector into Direction
    for (const Position& pos : adjancent_positions) {
        Direction dir = get_direction_from_position(pos);
        directions.push_back(dir);
    }
    return directions;
}

bool is_available_direction(std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {
    std::vector<Direction> directions = available_directions(g, index);
    Direction actual_direction = g->getDirection();

    for (const Direction& dir : directions){
        if (dir == actual_direction){
            return true;
        }
    }
    return false;
}

bool is_on_a_corner(int directions_size, std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {
    float x,y;
    x = g->getPosition().getX();
    y = g->getPosition().getY();

    if ( (directions_size == 2) && (!is_available_direction(g, index)) &&
         (is_approximated_to_integer(x, 0.2)) && (is_approximated_to_integer(y,0.2)) ){
        return true;
    }

    return false;
}

bool is_available(std::shared_ptr<EntityModel> e, Direction target_direction, std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {
    std::vector<Direction> directions = available_directions(e, index);

    //to check if target_direction is in directions
    auto it = std::find(directions.begin(),
                        directions.end(), target_direction);

    return it != directions.end();
}

bool is_point_in_interval (float point, float x){
    return (point >= x- 0.5) && (point <= x + 0.5);
}