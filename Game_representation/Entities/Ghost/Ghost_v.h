#ifndef PACMANV0_GHOST_V_H
#define PACMANV0_GHOST_V_H
#include <iostream>
#include "../EntityView.h"
#include "../../../Game_logic/Entities/Ghost/Ghost.h"

class Ghost_v : public EntityView {
public:
    Ghost_v() = default;
    Ghost_v(std::shared_ptr<Ghost> entity_ghost);
    void update(const std::string& message) override;
    void draw(int x, int y) override;
    void scaried_behaviour();
private:
    sf::Clock _clock;
    sf::Time _last_draw_time = sf::Time::Zero;
    sf::Time _start_time = _clock.getElapsedTime();
};


#endif //PACMANV0_GHOST_V_H
