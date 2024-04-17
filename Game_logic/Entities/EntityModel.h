#ifndef PACMANV0_ENTITYMODEL_H
#define PACMANV0_ENTITYMODEL_H
#include "../Observer/Subject.h"
#include <iostream>
#include <list>
#include <memory>
#include "../Utils/Position.h"

enum class Direction{ None, Up, Down, Left, Right };


class EntityModel : public Subject {
public:
    EntityModel(float speed);
    EntityModel() = default;

    void attach(std::shared_ptr<Observer> observer) override;
    void detach(std::shared_ptr<Observer> observer) override;
    void notify(const std::string& message) override;

    void setPosition(float x, float y);
    Position getPosition();
    void setDirection(Direction dir);
    Direction getDirection();
    float getSpeed();
    void setSpeed(float speed);
    virtual int getType();

    void move(double deltatime);
    void tick(double deltatime);

    Direction opposite_dir();

private:
    Direction _dir;
    int _type;
    float _speed = 0;
    std::list<std::shared_ptr<Observer>> _list_observers;
    std::string _message;

protected:
    Position _position = Position(0,0); // Provide a default constructor for _position

};


#endif //PACMANV0_ENTITYMODEL_H