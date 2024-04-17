#ifndef PACMANV0_SUBJECT_H
#define PACMANV0_SUBJECT_H

#include <memory>
#include "Observer.h"

class Subject {
public:
    virtual ~Subject(){};
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify(const std::string& message) = 0;
};


#endif //PACMANV0_SUBJECT_HH