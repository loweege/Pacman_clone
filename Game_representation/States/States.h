
#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_STATES_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_STATES_H
#include <memory>
#include "../Concrete_factory/EntityFactory.h"
#include "../../Game_logic/World.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Window.h"
#include "../../Game_logic/Utils/Utils.h"
#include "../../Game_logic/Entities/PacMan/PacmanMovement.h"
class StateManager;

enum StateType {
    NoState,
    MainMenu,
    Level,
    Pause,
    Victory,
    GameOver
};

class State {
protected:
    std::shared_ptr<StateManager> m_state_mng;

    virtual void mouse_click(){};
    virtual void handle_input(){ } ;
public:
    virtual ~State() = default;
    virtual void enter() { } ;
    virtual void exit(){ } ;
    virtual void update(float ) { } ;
    virtual void draw() { } ;
    [[nodiscard]] virtual StateType get_type() const { } ;
};

class MenuState : public State {
private:
    sf::Font _font;
    sf::Text _text;
    sf::Vector2f _button_size;
    sf::Vector2f _button_pos;
    unsigned int m_button_padding;
    sf::RectangleShape _rects[3];
    sf::Text _labels[3];
    std::vector<unsigned long> m_top_scores;
    std::vector<sf::Text> m_score_texts;
    sf::Text m_top_scores_label;

private:
    void mouse_click() override;

public:
    explicit MenuState(std::shared_ptr<StateManager> state_mng);

    void enter() override;
    void exit() override;
    void handle_input() override;

    void update(float) override;
    void draw() override;
    [[nodiscard]] inline StateType get_type() const override {
        return StateType::MainMenu;
    }
};

class LevelState : public State {
private:
    std::shared_ptr<Ghost> g1 ;
    std::shared_ptr<Ghost> g2 ;
    std::shared_ptr<Ghost> g3 ;
    std::shared_ptr<Ghost> g4 ;

    float pacman_speed = 3;
    float ghost_high_speed = 2;
    float ghost_low_speed = 0.75;

    float berserk_mode_time = 5.0f;
    float enable_movement1 = 5.0f;
    float enable_movement2 = 10.0f;
    bool trigger1 = false;
    bool trigger2 = false;
    bool trigger3 = false;

    sf::Clock berserk_clock;
    sf::Clock ghost_clock;
    std::vector<std::vector<std::shared_ptr<EntityModel>>> index;
    std::vector<std::shared_ptr<EntityModel>> entities ;
    std::shared_ptr<PacMan> pacman;
    std::vector<std::shared_ptr<Ghost>> ghosts ;
    std::vector<std::shared_ptr<Fruit>> fruits ;
    std::vector<std::shared_ptr<Coin>> coins ;

    std::shared_ptr<EntityFactory> m_entity_factory{nullptr};
    std::shared_ptr<World> m_world{nullptr};
    Direction desired_direction = Direction::None;
    sf::Text m_score_label;
    sf::Text m_life_label;

    int m_current_level {0};

    void player_controller(std::shared_ptr<PacMan> pacman,
                           std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
                           Direction desired_direction);

    void print_elements(std::vector<std::vector<std::shared_ptr<EntityModel>>> index);
    void fruits_checker(std::vector<std::shared_ptr<Fruit>> fruits, std::shared_ptr<PacMan> pacman);

    void dynamic_ghosts_speed_regulation(std::vector<std::shared_ptr<Ghost>> ghosts,
                                         std::shared_ptr<PacMan> pacman,
                                         float high_speed, float low_speed);

    void stop(std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Ghost>> ghosts);
    void respawn_moving_entities(std::shared_ptr<PacMan> pacman,
                                 std::vector<std::shared_ptr<Ghost>> ghosts,
                                 float pacman_speed, float ghost_speed);

public:

    explicit LevelState(std::shared_ptr<StateManager> state_mng, int difficulty);
    void enter() override;
    void exit() override;
    void handle_input() override;
    void update(float) override;
    void draw() override;
    [[nodiscard]] inline StateType get_type() const override {
        return StateType::Level;
    }
};

class PausedState : public State {
private:
    sf::Font _font;
    sf::Text _text;
    sf::Vector2f _button_size;
    sf::Vector2f _button_pos;
    unsigned int _button_padding;
    sf::RectangleShape _rects[2];
    sf::Text _labels[2];

    void mouse_click() override;
public:
    explicit PausedState(std::shared_ptr<StateManager> state_mng);
    void enter() override;
    void exit() override;
    void handle_input() override;
    void update(float) override;
    void draw() override;
    [[nodiscard]] inline StateType get_type() const override {
        return StateType::Pause;
    }

};



class GameOverState : public State {
protected:
    sf::Font _font;
    sf::Text text;
    sf::Text shadow;
public:
    explicit GameOverState(std::shared_ptr<StateManager> state_mng);
    void enter() override;
    void exit() override;
    void handle_input() override;
    void update(float) override;
    void draw() override;
    [[nodiscard]] inline StateType get_type() const override {
        return StateType::GameOver;
    }
};

class VictoryState : public GameOverState {

public:
    explicit VictoryState(std::shared_ptr<StateManager> state_mng);
    void handle_input() override;
    void enter() override;
    [[nodiscard]] inline StateType get_type() const override {
        return StateType::Victory;
    }
};


#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_STATES_H
