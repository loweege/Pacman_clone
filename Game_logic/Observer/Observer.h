#ifndef PACMANV0_OBSERVER_H
#define PACMANV0_OBSERVER_H
#include "iostream"

class Observer {
public:
    virtual ~Observer() {};
    virtual void update(const std::string &message) = 0;
};


#endif //PACMANV0_OBSERVER_H