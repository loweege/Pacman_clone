#ifndef PACMANV0_WALL_V_H
#define PACMANV0_WALL_V_H
#include "../EntityView.h"
#include "../../../Game_logic/Entities/Wall/Wall.h"
#include "SFML/Graphics.hpp"

class Wall_v : public EntityView {
public:
    Wall_v() = default;
    Wall_v(std::shared_ptr<Wall> wall_model);
    void update(const std::string& message) override;

    void draw(int x, int y) override;


};


#endif //PACMANV0_WALL_V_H
