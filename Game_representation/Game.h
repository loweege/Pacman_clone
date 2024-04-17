#ifndef PACMANV0_GAME_H
#define PACMANV0_GAME_H
#include <iostream>
#include <memory>
#include "../Game_logic/Entities/PacMan/PacmanMovement.h"
#include "SFML/Graphics.hpp"
#include "StateManager/StateManager.h"
extern bool running;

class Game {
public:
    Game();
    void run();
private:
    std::shared_ptr<StateManager> state_m;
};


#endif //PACMANV0_GAME_H
