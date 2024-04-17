#ifndef PACMANV0_UTILS_H
#define PACMANV0_UTILS_H
#include "../World.h"


bool is_in_the_right_position(float n, float m);

bool is_approximated_to_integer(float number, float tolerance);

bool is_on_an_intersection(int directions_size, std::shared_ptr<EntityModel> g);

Direction get_direction_from_position(const Position& diff);

Position get_position_difference_from_direction(Direction dir);

std::vector<Direction> available_directions(std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

bool is_available_direction(std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

bool is_on_a_corner(int directions_size, std::shared_ptr<EntityModel> g, std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

bool is_available(std::shared_ptr<EntityModel> e, Direction target_direction, std::vector<std::vector<std::shared_ptr<EntityModel>>> index);

bool is_point_in_interval (float point, float x);




#endif //PACMANV0_UTILS_H
