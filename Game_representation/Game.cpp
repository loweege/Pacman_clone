#include "Game.h"
#include "iostream"
#include <fstream>
#include <chrono>
#include <thread>
#include "../Game_logic/Utils/Stopwatch.h"
#include <SFML/Graphics.hpp>
#include "../Game_representation/Camera/Camera.h"
#include "../Game_logic/Ghost_AI/Ghost_AI.h"
#include "../Game_representation/Utils/Window.h"

std::shared_ptr<Score> score_m;


Window& window = Window::instance();
int window_width = window.get_window_width();
int window_height = window.get_window_height();

Camera camera(window_width, window_height);

Random Random::_instance;


void Game::run(){

    while (running && state_m) {

        auto deltatime = Stopwatch::get_instance().deltatime();
        double target_frame_time = 1.0 / 60.0;

        if (deltatime < target_frame_time) {
            std::this_thread::sleep_for
                    (std::chrono::duration<double>(target_frame_time - deltatime));
        }

        state_m->update(deltatime);
        state_m->draw();
    }

    /*std::ifstream file("../Game_logic/Utils/Map.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'Map.json'" << std::endl;
    }

    json j;
    file >> j;
    std::string string_map = j.dump();
    World w(string_map);


    const auto& index = w.get_positional_index();
    std::vector<std::shared_ptr<EntityModel>> entities = w.get_entities();
    std::shared_ptr<PacMan> pacman = w.get_pacman();
    std::vector<std::shared_ptr<Ghost>> ghosts = w.get_ghosts();
    std::vector<std::shared_ptr<Fruit>> fruits = w.get_fruits();
    std::vector<std::shared_ptr<Coin>> coins = w.get_coins();

    //init ghosts directions
    std::shared_ptr<Ghost> g1 = ghosts[0];
    std::shared_ptr<Ghost> g2 = ghosts[1];
    std::shared_ptr<Ghost> g3 = ghosts[2];
    std::shared_ptr<Ghost> g4 = ghosts[3];

    g1->setDirection(Direction::Right);
    g2->setDirection(Direction::Up);
    g3->setDirection(Direction::Up);
    g4->setDirection(Direction::Left);

    bool trigger1 = false;
    bool trigger2 = false;
    bool trigger3 = false;

    sf::Clock berserk_clock;
    sf::Clock ghost_clock;

    float berserk_mode_time = 5.0f;
    float enable_movement1 = 5.0f;
    float enable_movement2 = 10.0f;

    float pacman_speed = 3;
    float ghost_high_speed = 2;
    float ghost_low_speed = 0.75;

    std::shared_ptr<Score> score;

    while (window.get_window().isOpen()) {
        auto deltatime = Stopwatch::get_instance().deltatime();
        double target_frame_time = 1.0 / 60.0;

        if (deltatime < target_frame_time) {
            std::this_thread::sleep_for
                    (std::chrono::duration<double>(target_frame_time - deltatime));
        }

        sf::Event event;

        Direction desired_direction = Direction::None;

        while (window.get_window().pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        desired_direction = Direction::Up;
                        break;
                    case sf::Keyboard::Down:
                        desired_direction = Direction::Down;
                        break;
                    case sf::Keyboard::Left:
                        desired_direction = Direction::Left;
                        break;
                    case sf::Keyboard::Right:
                        desired_direction = Direction::Right;
                        break;
                    default:
                        break;
                }
            }
        }


        std::vector<Direction> directions = available_directions(pacman, index);


        player_controller(pacman, index, desired_direction);


        pacman_movement(pacman, deltatime, index, fruits, ghosts, coins);
        //check if the fruits have been eaten
        fruits_checker(fruits, pacman);
        //check if the fruits have been eaten
        dynamic_ghosts_speed_regulation(ghosts, pacman, ghost_high_speed, ghost_low_speed);


        if (!pacman->get_is_alive()) {
            stop(pacman, ghosts);
            respawn_moving_entities(pacman, ghosts, pacman_speed, ghost_high_speed);

            pacman->set_is_alive(true);
        }



        //enable berserk mode after berserk_mode_time seconds
        if (pacman->get_berserk_mode()) {
            if (berserk_clock.getElapsedTime().asSeconds() >= berserk_mode_time) {
                // Reset the clock and disable berserk mode
                berserk_clock.restart();
                pacman->set_berserk_mode(false);
            }
        } else {
            // If berserk mode is not active, reset the clock
            berserk_clock.restart();
        }


        //is out of the spawner
        float x1, y1;
        x1 = g1->getPosition().getX();
        y1 = g1->getPosition().getY();

        if (((is_in_the_right_position(x1, 5)) && (is_in_the_right_position(y1, 6))) ||
            ((is_in_the_right_position(x1, 5)) && (is_in_the_right_position(y1, 13)))) {
            trigger1 = true;
        }

        //is out of the spawner
        float x2, y2;
        x2 = g2->getPosition().getX();
        y2 = g2->getPosition().getY();

        if (((is_in_the_right_position(x2, 5)) && (is_in_the_right_position(y2, 6))) ||
            ((is_in_the_right_position(x2, 5)) && (is_in_the_right_position(y2, 13)))) {
            trigger2 = true;
        }

        //is out of the spawner
        float x3, y3;
        x3 = g3->getPosition().getX();
        y3 = g3->getPosition().getY();

        if (((is_in_the_right_position(x3, 5)) && (is_in_the_right_position(y3, 6))) ||
            ((is_in_the_right_position(x3, 5)) && (is_in_the_right_position(y3, 13)))) {
            trigger3 = true;
        }


        //ghost_trigger_right_behaviour
        if (!trigger1) {
            ghost_out_of_the_spawner(g1, deltatime);
            ghost_out_of_the_spawner(g4, deltatime);
        } else {
            ghost_AI(g1, index, pacman);
            g1->tick(deltatime);

            ghost_AI(g4, index, pacman);
            g4->tick(deltatime);
        }

        //to let the last 2 ghosts come out of the spawner after a certain amount of time
        if (!trigger2) {
            if (ghost_clock.getElapsedTime().asSeconds() >= enable_movement1) {
                ghost_out_of_the_spawner(g2, deltatime);
            }
        } else {
            //to know the amount of time passed
            if (ghost_clock.getElapsedTime().asSeconds() >= enable_movement1) {
                ghost_AI(g2, index, pacman);
                g2->tick(deltatime);
            }
        }


        if (!trigger3) {
            if (ghost_clock.getElapsedTime().asSeconds() >= enable_movement2) {
                ghost_out_of_the_spawner(g3, deltatime);
            }
        } else {
            if (ghost_clock.getElapsedTime().asSeconds() >= enable_movement2) {
                ghost_AI(g3, index, pacman);
                g3->tick(deltatime);
            }
        }






        // Clear the window
        window.get_window().clear();

        print_elements(index);
        //std::cout << score->get_score() << std::endl;

        // Display what was drawn
        window.get_window().display();
    }
*/


}

Game::Game() {
    state_m = std::make_shared<StateManager>();
    score_m = std::make_shared<Score>();
    if(state_m)
        state_m->push_state(std::make_unique<class MenuState>(state_m));
}




