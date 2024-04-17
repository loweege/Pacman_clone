#ifndef PACMANV0_PACMAN_H
#define PACMANV0_PACMAN_H
#include "../EntityModel.h"
#include "../Collectable/Collectable.h"
#include "../Ghost/Ghost.h"
#include "../../Score/Score.h"

class PacMan : public EntityModel {
public:
    PacMan(float speed);
    PacMan() = default;

    int getType() override;
    void set_berserk_mode(bool berserk);
    bool get_berserk_mode();
    void set_is_alive(bool is_alive);
    bool get_is_alive();

    void eat(std::shared_ptr<Collectable> c);
    void die();

private:
    int _life = 3;
    int _type = 1;
    bool _berserk = false;
    bool _is_alive = true;
};


#endif //PACMANV0_PACMAN_H