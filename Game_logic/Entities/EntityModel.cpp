#include "EntityModel.h"
#include "../Observer/Observer.h"
#include "math.h"


EntityModel::EntityModel(float speed) : _speed{speed} {};


void EntityModel::setPosition(float x, float y) {
    _position = {x,y};
}

Position EntityModel::getPosition() {
    return _position;
}

void EntityModel::setDirection(Direction dir){
    _dir = dir;
}

Direction EntityModel::getDirection() {
    return _dir;
}

void EntityModel::setSpeed(float speed) {
    _speed = speed;
}

float EntityModel::getSpeed() {
    return _speed;
}

int EntityModel::getType() {
    return _type;
}







void EntityModel::attach(std::shared_ptr<Observer> observer) {
    _list_observers.push_back(observer);
}

void EntityModel::detach(std::shared_ptr<Observer> observer) {
    _list_observers.remove(observer);
}

void EntityModel::notify(const std::string& message) {
    for (auto &obs: _list_observers) {
        obs->update(message);
    }
}

void EntityModel::tick(double deltatime) {
    if(_dir == Direction::None)
        return;

    move(deltatime);
}

void EntityModel::move(double deltatime){
    float pixels_per_frame = _speed * deltatime;

    if (_dir == Direction::Left){
        this->setPosition(this->_position.getX(),this->_position.getY() - pixels_per_frame);
    } else if (_dir == Direction::Right){
        this->setPosition(this->_position.getX(),this->_position.getY() + pixels_per_frame);
    } else if (_dir == Direction::Up){
        this->setPosition(this->_position.getX() - pixels_per_frame,this->_position.getY());
    } else if (_dir == Direction::Down){
        this->setPosition(this->_position.getX() + pixels_per_frame,this->_position.getY());
    }

}

Direction EntityModel::opposite_dir() {
    if (_dir == Direction::Up)
        return Direction::Down;

    if (_dir == Direction::Down)
        return Direction::Up;

    if (_dir == Direction::Left)
        return Direction::Right;

    if (_dir == Direction::Right)
        return Direction::Left;

    if (_dir == Direction::None)
        return _dir;

    return Direction::None;
}