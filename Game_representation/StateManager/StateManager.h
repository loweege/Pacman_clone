//
// Created by r1per on 7/01/24.
//

#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_STATEMANAGER_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_STATEMANAGER_H
#include <iostream>
#include <stack>
#include <memory>
#include "../States/States.h"

class StateManager: public std::enable_shared_from_this<StateManager>
{
private:
    std::stack<std::unique_ptr<State>> states;
public:

    explicit StateManager() = default;

    StateType get_current_state() const ;

    void push_state(std::unique_ptr<State> state);

    void pop_state();

    void transit_to(StateType);

    void update(float deltatime);

    void draw();

    ~StateManager();

};



#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_STATEMANAGER_H
