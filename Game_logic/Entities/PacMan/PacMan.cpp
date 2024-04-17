#include "PacMan.h"
#include "../Collectable/Collectable.h"
#include "../../Score/Score.h"

PacMan::PacMan(float speed) : EntityModel(speed) {};

void PacMan::die() {
    _life--;
    _is_alive = false;
    this->setPosition(9,9);//starting position of pacman
}

void PacMan::eat(std::shared_ptr<Collectable> c) {
    if (c->getType() == 4 && c->get_is_alive()) {
        _berserk = true;
    }
}

int PacMan::getType() {
    return _type;
}

bool PacMan::get_berserk_mode() {
    return _berserk;
}

void PacMan::set_berserk_mode(bool berserk) {
    _berserk = berserk;
}

void PacMan::set_is_alive(bool is_alive) {
    _is_alive = is_alive;
}

bool PacMan::get_is_alive() {
    return _is_alive;
}
