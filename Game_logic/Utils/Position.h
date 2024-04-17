#ifndef PACMANV0_POSITION_H
#define PACMANV0_POSITION_H

#include <iostream>

class Position {
public:
    Position(float x, float y) : _x{x}, _y{y} {};

    float getX() const {
        return _x;
    };

    float getY() const {
        return _y;
    };

    friend bool operator==(const Position& lhs, const Position& rhs);
    friend Position operator+(const Position& lhs, const Position& rhs);

private:
    float _x;
    float _y;
};

inline bool operator==(const Position& lhs, const Position& rhs) {
    return (lhs._x == rhs._x) && (lhs._y == rhs._y);
}

inline Position operator+(const Position& lhs, const Position& rhs) {
    return {lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY()};
}

/*
std::ostream& operator<<(std::ostream& os, const Position& position) {
    os << "(" << position.getX() << ", " << position.getY() << ")";
    return os;
}
*/
#endif //PACMANV0_POSITION_H
