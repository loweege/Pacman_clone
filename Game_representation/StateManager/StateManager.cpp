#include "StateManager.h"

StateType StateManager::get_current_state() const
{
    if (!states.empty()) {
        return states.top()->get_type();
    }
    else {
        return StateType::NoState;
    }
}
void StateManager::push_state(std::unique_ptr<State> state)
{
    if (!states.empty()) {
        states.top()->exit();
    }
    states.push(std::move(state));
    states.top()->enter();
}

void StateManager::pop_state()
{
    if (!states.empty()) {
        states.top()->exit();
        states.pop();
        if (!states.empty()) {
            states.top()->enter();
        }
    }
}

void StateManager::update(float deltatime)
{
    if (!states.empty()) {
        states.top()->update(deltatime);
    }
}

void StateManager::draw()
{
    if (!states.empty()) {
        states.top()->draw();
    }
}

StateManager::~StateManager()
{
    while (!states.empty()) {
        states.top()->exit();
        states.pop();
    }
}

void StateManager::transit_to(StateType to){
    auto current_state = get_current_state();

    if(!score_m)
        return;

    switch(current_state){

        case NoState:
            break;
        case MainMenu:{
            if(to == Level){
                score_m->reset();
                push_state(std::make_unique<LevelState>(shared_from_this(),  score_m->current_level));
                break;
            }
        }
        case Level:{
            if( to == Pause)
                push_state(std::make_unique<PausedState>(shared_from_this()));
            else if( to == Victory) {
                score_m->current_level++;
                push_state(std::make_unique<VictoryState>(shared_from_this()));
            }
            else if(to == GameOver) {
                push_state(std::make_unique<GameOverState>(shared_from_this()));
            }
            break;
        }

        case Pause:{
            if(to == MainMenu){
                while(!states.empty())
                    pop_state();
                score_m->reset();
                push_state(std::make_unique<MenuState>(shared_from_this()));
            }
            else if(to == Level){
                pop_state();
            }
            break;
        }

        case Victory:{
            if( to == Level){
                while(!states.empty())
                    pop_state();

                push_state(std::make_unique<MenuState>(shared_from_this()));
                push_state(std::make_unique<LevelState>(shared_from_this(),  score_m->current_level));
            }
            break;
        }

        case GameOver:{
            if(to == MainMenu){
                while(!states.empty())
                    pop_state();

                score_m->reset();
                push_state(std::make_unique<MenuState>(shared_from_this()));
            }
            break;
        }
    }
}