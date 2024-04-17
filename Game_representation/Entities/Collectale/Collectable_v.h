#ifndef PACMANV0_COLLECTABLE_V_H
#define PACMANV0_COLLECTABLE_V_H
#include "../EntityView.h"
#include "../../../Game_logic/Entities/Collectable/Collectable.h"

class Collectable_v : public EntityView {
public:
    Collectable_v() = default;
    Collectable_v(std::shared_ptr<Collectable> collectable_model);
    void update(const std::string& message) override;
    void draw(int x, int y) override;

};


#endif //PACMANV0_COLLECTABLE_V_H
