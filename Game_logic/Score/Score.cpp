#include "Score.h"



void Score::update(const std::string &message) {
    if( message == "pacman killed")
        _life_left--;

    if (message == "coin"){
        coin_score();
    }
    if (message == "fruit"){
        fruit_score();
    }
    if (message == "ghost"){
        ghost_score();
    }
    if (message == "level finished"){
        level_finished_score();
    }
}

void Score::coin_score() {
    _score += 10;
}

void Score::fruit_score() {
    _score += 50;
}

void Score::ghost_score() {
    _score += 200;
}

void Score::level_finished_score() {
    _score += 1000;
}

int Score::get_score() {
    return _score;
}