#include "PacmanMovement.h"


std::vector<Direction> available_directions_for_pacman(
        std::shared_ptr<EntityModel> g,
        std::vector<std::vector<std::shared_ptr<EntityModel>>> index) {


    std::vector<Position> adjancent_positions = {{-1, 0}, {1, 0},
                                                 {0, 1}, {0, -1}};

    std::vector<Direction> directions;

    // Use iterator to remove directions that satisfy the condition
    adjancent_positions.erase(
            std::remove_if(
                    adjancent_positions.begin(),
                    adjancent_positions.end(),
                    [&](const Position& pos) {

                        Position next_position(0,0);



                        //left
                        if (pos.getX() == 0 && pos.getY()==-1){
                            if ( abs(g->getPosition().getY() - int(g->getPosition().getY())) > 0.05){
                                //rounded up
                                next_position =
                                        {roundf(g->getPosition().getX() + pos.getX()),
                                         std::floor(g->getPosition().getY() + pos.getY())};
                            } else{
                                //rounded down
                                next_position =
                                        {roundf(g->getPosition().getX() + pos.getX()),
                                         std::ceil(g->getPosition().getY() + pos.getY())};
                            }
                        }

                        //right
                        if (pos.getX() == 0 && pos.getY()==1){
                            if ( abs(g->getPosition().getY() - int(g->getPosition().getY())) > 0.95){
                                //rounded up
                                next_position =
                                        {roundf(g->getPosition().getX() + pos.getX()),
                                         std::ceil(g->getPosition().getY() + pos.getY())};
                            } else{
                                //rounded down
                                next_position =
                                        {roundf(g->getPosition().getX() + pos.getX()),
                                         std::floor(g->getPosition().getY() + pos.getY())};
                            }
                        }

                        //up
                        if (pos.getX() == -1 && pos.getY() == 0){
                            if ( abs(g->getPosition().getX() - int(g->getPosition().getX())) > 0.95){
                                //rounded up
                                next_position =
                                        {std::floor(g->getPosition().getX() + pos.getX()),
                                         roundf(g->getPosition().getY() + pos.getY())};
                            } else{
                                //rounded down
                                next_position =
                                        {std::ceil(g->getPosition().getX() + pos.getX()),
                                         roundf(g->getPosition().getY() + pos.getY())};
                            }

                        }

                        //down
                        if (pos.getX() == 1 && pos.getY() == 0){
                            if ( abs(g->getPosition().getX() - int(g->getPosition().getX())) > 0.05){
                                //rounded up
                                next_position =
                                        {std::ceil(g->getPosition().getX() + pos.getX()),
                                         roundf(g->getPosition().getY() + pos.getY())};
                            } else{
                                //rounded down
                                next_position =
                                        {std::floor(g->getPosition().getX() + pos.getX()),
                                         roundf(g->getPosition().getY() + pos.getY())};
                            }

                        }


                        std::shared_ptr<EntityModel> neighbor = index[next_position.getX()][next_position.getY()];
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










void handle_wall_collision(
        std::shared_ptr<EntityModel> e, double deltatime,
        std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
        std::vector<std::shared_ptr<Fruit>> fruits) {

    std::vector<Direction> directions = available_directions_for_pacman(e, index);

    if (std::find(directions.begin(), directions.end(), e->getDirection())
        != directions.end()) {
        e->tick(deltatime);
    }
}

void check_fruits(
        std::shared_ptr<PacMan> pacman,
        std::vector<std::shared_ptr<Fruit>> fruits,
        std::shared_ptr<Fruit> fruit_p) {

    for (const auto& fruit : fruits) {
        if (fruit_p == fruit) {
            fruit->set_is_eaten();
            pacman->eat(fruit);
            break;
        }
    }
}

void check_coins(
        std::shared_ptr<PacMan> pacman,
        std::vector<std::shared_ptr<Coin>> coins,
        std::shared_ptr<Coin> coin_p) {

    for (const auto& coin : coins) {
        if (coin_p == coin) {
            if(!coin->get_is_eaten()){
                pacman->notify("coin");
                coin->set_is_eaten();
            }
            pacman->eat(coin);
            break;
        }
    }

}

Position approxima(std::shared_ptr<PacMan> pacman) {
    Position approx_position(0,0);

    // if you go left
    if (pacman->getDirection() == Direction::Left){
        auto pos = get_position_difference_from_direction(Direction::Left);
        if ( abs(pacman->getPosition().getY() - int(pacman->getPosition().getY())) > 0.05){
            //rounded up
            approx_position =
                    {roundf(pacman->getPosition().getX() + pos.getX()),
                     std::floor(pacman->getPosition().getY() + pos.getY())};
        } else{
            //rounded down
            approx_position =
                    {roundf(pacman->getPosition().getX() + pos.getX()),
                     std::ceil(pacman->getPosition().getY() + pos.getY())};
        }
    }

    //right
    if (pacman->getDirection() == Direction::Right){
        auto pos = get_position_difference_from_direction(Direction::Right);
        if ( abs(pacman->getPosition().getY() - int(pacman->getPosition().getY())) > 0.95){
            //rounded up
            approx_position =
                    {roundf(pacman->getPosition().getX() + pos.getX()),
                     std::ceil(pacman->getPosition().getY() + pos.getY())};
        } else{
            //rounded down
            approx_position =
                    {roundf(pacman->getPosition().getX() + pos.getX()),
                     std::floor(pacman->getPosition().getY() + pos.getY())};
        }
    }

    //up
    if (pacman->getDirection() == Direction::Up){
        auto pos = get_position_difference_from_direction(Direction::Up);
        if ( abs(pacman->getPosition().getX() - int(pacman->getPosition().getX())) > 0.95){
            //rounded up
            approx_position =
                    {std::floor(pacman->getPosition().getX() + pos.getX()),
                     roundf(pacman->getPosition().getY() + pos.getY())};
        } else{
            //rounded down
            approx_position =
                    {std::ceil(pacman->getPosition().getX() + pos.getX()),
                     roundf(pacman->getPosition().getY() + pos.getY())};
        }
    }

    //down
    if (pacman->getDirection() == Direction::Down){
        auto pos = get_position_difference_from_direction(Direction::Down);
        if ( abs(pacman->getPosition().getX() - int(pacman->getPosition().getX())) > 0.05){
            //rounded up
            approx_position =
                    {std::ceil(pacman->getPosition().getX() + pos.getX()),
                     roundf(pacman->getPosition().getY() + pos.getY())};
        } else{
            //rounded down
            approx_position =
                    {std::floor(pacman->getPosition().getX() + pos.getX()),
                     roundf(pacman->getPosition().getY() + pos.getY())};
        }
    }

    return approx_position;
}

void handle_ghost_collision(
        std::shared_ptr<PacMan> pacman,
        std::vector<std::shared_ptr<Ghost>> ghosts) {

    float x = pacman->getPosition().getX();
    float y = pacman->getPosition().getY();

    for (const auto& ghost : ghosts) {
        if (is_point_in_interval(ghost->getPosition().getX(), x) &&
            is_point_in_interval(ghost->getPosition().getY(), y)) {
            if (!pacman->get_berserk_mode()) {
                pacman->die();
                pacman->notify("pacman killed");
            } else {
                ghost->respawn();
            }
            break;
        }
    }
}

void pacman_movement(
        std::shared_ptr<PacMan> pacman, double deltatime,
        std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
        std::vector<std::shared_ptr<Fruit>> fruits,
        std::vector<std::shared_ptr<Ghost>> ghosts,
        std::vector<std::shared_ptr<Coin>> coins) {

    handle_wall_collision(pacman, deltatime, index, fruits);
    handle_ghost_collision(pacman, ghosts);

    Position regularized_pacman_position = approxima(pacman);
    std::shared_ptr<EntityModel> entity = index[regularized_pacman_position.getX()][regularized_pacman_position.getY()];


    if (entity) {
        std::shared_ptr<Coin> coin_ptr = std::dynamic_pointer_cast<Coin>(entity);
        if (coin_ptr) {
            check_coins(pacman, coins, coin_ptr);
        } else {
            std::shared_ptr<Fruit> fruit_ptr = std::dynamic_pointer_cast<Fruit>(entity);
            if (fruit_ptr) {
                check_fruits(pacman, fruits, fruit_ptr);
            }
        }
    }

}
