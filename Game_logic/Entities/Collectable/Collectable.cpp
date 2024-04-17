#include "Collectable.h"


bool Collectable::get_is_eaten() {
    return _is_eaten;
}

void Collectable::set_is_eaten() {
    _is_eaten = true;
}

int Coin::getType() {
    return _type;
}

int Fruit::getType() {
    return _type;
}

bool Collectable::get_is_alive() {
    return _is_alive;
}

void Collectable::set_is_alive(bool is_alive) {
    _is_alive = is_alive;
}