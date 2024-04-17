#include "States.h"
#include "../StateManager/StateManager.h"
#include "../../Game_logic/Ghost_AI/Ghost_AI.h"
#include "../Game.h"

extern sf::Font g_font;
extern bool running;
void MenuState::enter() {

    _text.setFont(g_font);
    _text.setString(sf::String("PACMAN MAIN MENU:"));
    _text.setCharacterSize(48);
    sf::FloatRect text_rect = _text.getLocalBounds();
    _text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                     text_rect.top + text_rect.height / 2.0f);
    _text.setPosition(1000 / 2, 100);

    _button_size = sf::Vector2f(350.0f, 50.0f);
    _button_pos = sf::Vector2f(1000 / 2, 250);
    m_button_padding = 8;

    std::string str[3];
    str[0] = "PLAY";
    str[1] = "--PacMan--";
    str[2] = "EXIT";

    for (int i = 0; i < 3; ++i) {
        sf::Vector2f buttonPosition(_button_pos.x, _button_pos.y +
                                                    (i * (_button_size.y + m_button_padding)));
        _rects[i].setSize(_button_size);
        _rects[i].setFillColor(sf::Color(30, 144, 255));
        _rects[i].setOutlineColor(sf::Color::White);
        _rects[i].setOutlineThickness(2.0f);
        _rects[i].setOrigin(_button_size.x / 2.0f,
                             _button_size.y / 2.0f);
        _rects[i].setPosition(buttonPosition);

        _labels[i].setFont(g_font);
        _labels[i].setString(sf::String(str[i]));
        _labels[i].setCharacterSize(24);
        _labels[i].setFillColor(sf::Color::White);
        sf::FloatRect rect = _labels[i].getLocalBounds();
        _labels[i].setOrigin(rect.left + rect.width / 2.0f,
                              rect.top + rect.height / 2.0f);
        _labels[i].setPosition(buttonPosition);
    }

}

void MenuState::exit()
{
}

void MenuState::draw()
{

    window.get_window().clear(sf::Color::Black);

    window.get_window().draw(_text);

    window.get_window().draw(m_top_scores_label);

    for (auto& score_text : m_score_texts) {
        window.get_window().draw(score_text);
    }

    for (int i = 0; i < 3; ++i) {
        window.get_window().draw(_rects[i]);
        window.get_window().draw(_labels[i]);
    }

    // Update the window.get_window().
    window.get_window().display();

    // Update the window.get_window().
    window.get_window().display();
}

void MenuState::handle_input() {

    sf::Event event{};

    while (window.get_window().pollEvent(event)) {

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse_click();
            }
        }
    }
}

void MenuState::mouse_click() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window.get_window());
    float halfX = _button_size.x / 2.0f;
    float halfY = _button_size.y / 2.0f;

    for (int i = 0; i < 3; ++i) {
        if (mouse_pos.x >= _rects[i].getPosition().x - halfX &&
            mouse_pos.x <= _rects[i].getPosition().x + halfX &&
            mouse_pos.y >= _rects[i].getPosition().y - halfY &&
            mouse_pos.y <= _rects[i].getPosition().y + halfY) {
            if (i == 0) {
                m_state_mng->transit_to(Level);
            } else if (i == 1) {
                // Credits state.
            } else if (i == 2) {
                running = false;
            }
        }
    }
}

void MenuState::update(float deltatime) {
    handle_input();
}

MenuState::MenuState(std::shared_ptr<StateManager> state_mng) {
    m_state_mng = std::move(state_mng);
}

LevelState::LevelState(std::shared_ptr<StateManager> state_mng, int difficulty) {
    m_current_level = difficulty;
    m_state_mng = std::move(state_mng);
    std::ifstream file("../Game_logic/Utils/Map.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'Map.json'" << std::endl;
    }

    json j;
    file >> j;
    std::string string_map = j.dump();
    m_world = std::make_shared<World>(string_map, m_current_level);

    index = m_world->get_positional_index();
    entities = m_world->get_entities();
    pacman = m_world->get_pacman();
    ghosts = m_world->get_ghosts();
    fruits = m_world->get_fruits();
    coins = m_world->get_coins();

    //init ghosts directions
    g1 = ghosts[0];
    g2 = ghosts[1];
    g3 = ghosts[2];
    g4 = ghosts[3];

    g1->setDirection(Direction::Right);
    g2->setDirection(Direction::Up);
    g3->setDirection(Direction::Up);
    g4->setDirection(Direction::Left);

}

void LevelState::enter()
{


    if(!m_entity_factory)
        m_entity_factory = std::make_shared<EntityFactory>();

    if(m_world && m_world->get_pacman() && score_m )
        m_world->get_pacman()->attach(score_m);

    m_life_label.setFont(g_font);
    m_life_label.setString("Lifes Left: ");
    m_life_label.setCharacterSize(24);
    m_life_label.setFillColor(sf::Color::Yellow);
    m_life_label.setPosition(1000/2, 575);

    m_score_label.setFont(g_font);
    m_score_label.setString("Score:");
    m_score_label.setCharacterSize(24);
    m_score_label.setFillColor(sf::Color::Yellow);
    m_score_label.setPosition(5, 575 );

}

void LevelState::exit()
{

    if(m_world && pacman && score_m )
        pacman->detach(score_m);
}

void LevelState::handle_input() {
    if (!m_world)
        return;

    sf::Event event{};

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
                case sf::Keyboard::Escape:
                    m_state_mng->push_state(std::make_unique<PausedState>(m_state_mng));
                    break;
                default:
                    break;
            }
        }
    }

}
void LevelState::player_controller(std::shared_ptr<PacMan> pacman,
                                   std::vector<std::vector<std::shared_ptr<EntityModel>>> index,
                                   Direction desired_direction) {


    std::vector<Direction> directions = available_directions(pacman, index);

    //if desired_direction != None and there are no walls
    if (pacman->getDirection() == Direction::None){
        pacman->setDirection(desired_direction);
    } else
    if(is_available(pacman, desired_direction, index) && pacman->opposite_dir() == desired_direction){
        pacman->setDirection(desired_direction);



    } if (is_approximated_to_integer(pacman->getPosition().getX(), 0.2)  && is_approximated_to_integer(pacman->getPosition().getY(), 0.2)){
        if (is_available(pacman, desired_direction, index)){
            pacman->setDirection(desired_direction);
        }
    }

}

void LevelState::print_elements(std::vector<std::vector<std::shared_ptr<EntityModel>>> index){
    for (const auto &row: index) {
        for (const auto &element: row) {

            element->notify("draw");


        }
    }
}

void LevelState::fruits_checker(std::vector<std::shared_ptr<Fruit>> fruits,
                                std::shared_ptr<PacMan> pacman) {
    for (const auto& fruit : fruits) {
        if (fruit->get_is_eaten() && fruit->get_is_alive()) {
            fruit->set_is_alive(false);
            pacman->notify("fruit");
        }
    }
}

void LevelState::dynamic_ghosts_speed_regulation(std::vector<std::shared_ptr<Ghost>> ghosts, std::shared_ptr<PacMan> pacman,
                                                 float high_speed, float low_speed) {
    //dynamic_ghosts_speed_regulation
    double speed = (pacman->get_berserk_mode()) ? low_speed : high_speed;

    for (const auto& ghost : ghosts) {
        ghost->set_chasing_mode(!pacman->get_berserk_mode());
        ghost->setSpeed(speed);
    }
}

void LevelState::stop(std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Ghost>> ghosts){
    pacman->setSpeed(0);
    for (const auto& ghost : ghosts) {
        ghost->setSpeed(0);
    }
}

void LevelState::respawn_moving_entities(std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Ghost>> ghosts,
                                         float pacman_speed, float ghost_speed){


    pacman->setPosition(9,9);
    pacman->setSpeed(pacman_speed);

    ghosts[0]->setPosition(5,8);
    ghosts[1]->setPosition(5,9);
    ghosts[2]->setPosition(5,10);
    ghosts[3]->setPosition(5,11);


    //here I want that before the ghosts moves again they have to wait 2 seconds

    for (const auto& ghost : ghosts) {
        ghost->setSpeed(ghost_speed);
    }

}


void LevelState::update(float deltatime)
{
    if(!m_world)
        return;

    if(score_m ){
        if(score_m->is_victory())
            m_state_mng->transit_to(Victory);
        else if(score_m->is_game_over())
            m_state_mng->transit_to(GameOver);
    }

    handle_input();

    std::vector<Direction> directions = available_directions(m_world->get_pacman(), index);


    player_controller(m_world->get_pacman(), index, desired_direction);


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

}

void LevelState::draw()
{
    window.get_window().clear();

    print_elements(index);

    if(score_m){
        auto score = score_m->get_score();
        sf::Text score_value;
        score_value.setString(std::to_string(score));
        score_value.setFont(g_font);
        score_value.setCharacterSize(24);
        score_value.setFillColor(sf::Color::Yellow);
        score_value.setPosition(75, 575 );
        window.get_window().draw(m_score_label);
        window.get_window().draw(score_value);

        auto life_left = score_m->get_lifes();
        sf::Text life_value;
        life_value.setString(std::to_string(life_left));
        life_value.setFont(g_font);
        life_value.setCharacterSize(24);
        life_value.setFillColor(sf::Color::Yellow);
        life_value.setPosition(1000/2 +110, 575);
        window.get_window().draw(m_life_label);
        window.get_window().draw(life_value);


    }

    window.get_window().display();
}

void PausedState::enter()
{

    _text.setFont(g_font);
    _text.setString(sf::String("PAUSE:"));
    _text.setCharacterSize(36); // Increase the font size
    _text.setFillColor(sf::Color::Yellow); // Change text color
    sf::FloatRect text_rect = _text.getLocalBounds();
    _text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                    text_rect.top + text_rect.height / 2.0f);
    _text.setPosition(1000 / 2, 100);

    _button_size = sf::Vector2f(350.0f, 50.0f); // Increase button size
    _button_pos = sf::Vector2f(1000 / 2, 250);
    _button_padding = 8; // Increase button padding

    std::string str[2];
    str[0] = "CONTINUE";
    str[1] = "BACK TO MAIN MENU";

    for (int i = 0; i < 2; ++i) {
        sf::Vector2f buttonPosition(_button_pos.x, _button_pos.y +
                                                   (i * (_button_size.y + _button_padding)));
        _rects[i].setSize(_button_size);
        _rects[i].setFillColor(sf::Color(30, 144, 255)); // Change button color to Dodger Blue
        _rects[i].setOutlineColor(sf::Color::White); // Add a white outline
        _rects[i].setOutlineThickness(2.0f); // Set outline thickness
        _rects[i].setOrigin(_button_size.x / 2.0f,
                            _button_size.y / 2.0f);
        _rects[i].setPosition(buttonPosition);

        _labels[i].setFont(g_font);
        _labels[i].setString(sf::String(str[i]));
        _labels[i].setCharacterSize(24); // Decrease label size
        _labels[i].setFillColor(sf::Color::White); // Change label color to white
        sf::FloatRect rect = _labels[i].getLocalBounds();
        _labels[i].setOrigin(rect.left + rect.width / 2.0f,
                             rect.top + rect.height / 2.0f);
        _labels[i].setPosition(buttonPosition);
    }

}

void PausedState::exit()
{
}

void PausedState::handle_input() {
    sf::Event event{};

    while ( window.get_window().pollEvent(event)) {

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse_click();
            }
        }
    }
}


void PausedState::update(float deltatime)
{
    handle_input();
}

void PausedState::draw()
{
    window.get_window().clear(sf::Color::Black);

    window.get_window().draw(_text);
    for (int i = 0; i < 2; ++i) {
        window.get_window().draw(_rects[i]);
        window.get_window().draw(_labels[i]);
    }

    window.get_window().display();
    window.get_window().display();
}

PausedState::PausedState(std::shared_ptr<StateManager> state_mng) {
    m_state_mng = std::move(state_mng);
}

void PausedState::mouse_click() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window.get_window());
    float halfX = _button_size.x / 2.0f;
    float halfY = _button_size.y / 2.0f;

    // Check for the first button (PLAY)
    if (mouse_pos.x >= _rects[0].getPosition().x - halfX &&
        mouse_pos.x <= _rects[0].getPosition().x + halfX &&
        mouse_pos.y >= _rects[0].getPosition().y - halfY &&
        mouse_pos.y <= _rects[0].getPosition().y + halfY) {
        m_state_mng->transit_to(Level);
        return;
    }

    // Check for the second button (MainMenu)
    if (mouse_pos.x >= _rects[1].getPosition().x - halfX &&
        mouse_pos.x <= _rects[1].getPosition().x + halfX &&
        mouse_pos.y >= _rects[1].getPosition().y - halfY &&
        mouse_pos.y <= _rects[1].getPosition().y + halfY) {
        m_state_mng->transit_to(MainMenu);
        return;
    }
}


VictoryState::VictoryState(std::shared_ptr<StateManager> state_mng) : GameOverState(state_mng) {
    m_state_mng = std::move(state_mng);
}

void VictoryState::enter()
{
    shadow.setString("VICTORY");
    text.setString("VICTORY");
    shadow.setFont(g_font);
    shadow.setCharacterSize(50); // Large character size for emphasis
    shadow.setFillColor(sf::Color(50, 50, 50)); // Dark color for the shadow
    shadow.setPosition(42, 302);
    text.setFont(g_font);
    text.setCharacterSize(50); // Same size as the shadow
    text.setFillColor(sf::Color::Green); // Choose a color that stands out
    text.setPosition(500, 300);
}

void VictoryState::handle_input() {
    sf::Event event{};
    while (window.get_window().pollEvent(event)) {

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    m_state_mng->transit_to(Level);
                default:
                    break;
            }
        }
    }
}

void GameOverState::enter()
{
    text.setString("GAME OVER");

    text.setFont(g_font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White); // Choose a color that stands out
    text.setPosition(300, 300);
}

void GameOverState::exit()
{
}

void GameOverState::handle_input() {
    sf::Event event{};
    while (window.get_window().pollEvent(event)) {

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:{
                    m_state_mng->transit_to(MainMenu);
                }
                default:
                    break;
            }
        }
    }
}

void GameOverState::update(float deltatime)
{
    handle_input();
}

GameOverState::GameOverState(std::shared_ptr<StateManager> state_mng) {
    m_state_mng = std::move(state_mng);
}

void GameOverState::draw() {
    window.get_window().clear();
    window.get_window().draw(shadow); // Draw the shadow first
    window.get_window().draw(text);   // Then draw the text
    window.get_window().display();
}