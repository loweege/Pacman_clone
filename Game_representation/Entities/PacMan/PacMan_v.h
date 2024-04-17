#ifndef PACMANV0_PACMAN_V_H
#define PACMANV0_PACMAN_V_H
#include <iostream>
#include <memory>
#include "../../../Game_logic/Entities/PacMan/PacMan.h"
#include "../EntityView.h"

class PacMan_v : public EntityView{
public:
    PacMan_v() = default;
    PacMan_v(std::shared_ptr<PacMan> pacman_model);
    void update(const std::string& message) override;
    void draw(int x, int y) override;

private:
    sf::Clock _clock;
    sf::Time _last_draw_time = sf::Time::Zero;
    sf::Time _start_time = _clock.getElapsedTime();

};


#endif //PACMANV0_PACMAN_V_H
