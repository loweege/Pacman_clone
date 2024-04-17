#ifndef PACMANV0_COLLECTABLE_H
#define PACMANV0_COLLECTABLE_H
#include "../EntityModel.h"

class Collectable : public EntityModel{
public :
    Collectable() = default;
    void set_is_eaten();
    bool get_is_eaten();
    bool get_is_alive();
    void set_is_alive(bool is_alive);
private:
    bool _is_eaten;
    bool _is_alive = true;
};


class Coin : public Collectable {
public:
    Coin() = default;
    int getType() override;
private:
    int _type = 2;
};


class Fruit : public Collectable{
public:
    Fruit() = default;
    int getType() override;
private:
    int _type = 4;
};

#endif //PACMANV0_COLLECTABLE_H