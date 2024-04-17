#include "Ghost.h"

int Ghost::getType() {
    return _type;
}

bool Ghost::get_chasing_mode() {
    return _chasing_mode;
}

void Ghost::set_chasing_mode(bool chasing_mode) {
    _chasing_mode = chasing_mode;
}

void Ghost::respawn() {
    //spawner position
    setPosition(5,9);
}