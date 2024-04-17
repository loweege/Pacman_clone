#include "PacMan_v.h"

PacMan_v::PacMan_v(std::shared_ptr<PacMan> pacman_model) :
        EntityView(pacman_model){};

void PacMan_v::update(const std::string& message_from_subject) {
    if (message_from_subject == "draw") {

        if (_entity_model->getDirection() == Direction::Left ||
            _entity_model->getDirection() == Direction::None) {


            // Get the current time
            sf::Time current_time = _clock.getElapsedTime();

            // Calculate the time since the start
            sf::Time elapsed_time = current_time - _start_time;

            // Calculate the index of the current 0.5-second interval
            int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

            // Toggle between two positions every 0.5 seconds
            if (intervalIndex % 2 == 0) {
                draw(845, 345);
            } else {
                draw(845, 395);
            }

        }


        if (_entity_model->getDirection() == Direction::Up) {
            //draw(845, 495);

            // Get the current time
            sf::Time current_time = _clock.getElapsedTime();

            // Calculate the time since the start
            sf::Time elapsed_time = current_time - _start_time;

            // Calculate the index of the current 0.5-second interval
            int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

            // Toggle between two positions every 0.5 seconds
            if (intervalIndex % 2 == 0) {
                draw(845, 495);
            } else {
                draw(845, 545);
            }
        }


        if (_entity_model->getDirection() == Direction::Down) {
            //draw(845, 195);

            // Get the current time
            sf::Time current_time = _clock.getElapsedTime();

            // Calculate the time since the start
            sf::Time elapsed_time = current_time - _start_time;

            // Calculate the index of the current 0.5-second interval
            int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

            // Toggle between two positions every 0.5 seconds
            if (intervalIndex % 2 == 0) {
                draw(845, 195);
            } else {
                draw(845, 245);
            }
        }


        if (_entity_model->getDirection() == Direction::Right) {
            //draw(845, 45);

            // Get the current time
            sf::Time current_time = _clock.getElapsedTime();

            // Calculate the time since the start
            sf::Time elapsed_time = current_time - _start_time;

            // Calculate the index of the current 0.5-second interval
            int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

            // Toggle between two positions every 0.5 seconds
            if (intervalIndex % 2 == 0) {
                draw(845, 45);
            } else {
                draw(845, 95);
            }
        }
    }
}


void PacMan_v::draw(int x, int y) {
    if(!_entity_model)
        return;

    sf::Vector2f coordinates = camera.cell_to_pixel(_entity_model->getPosition().getX(),
                                                    _entity_model->getPosition().getY(), 12, 20);
    //sf::Texture texture;
    if (!_texture.loadFromFile("../Game_representation/Sprites/Sprites.png")){
        //handle error
    }

    // Define the rectangle to extract a 50x50 portion, adjust the left and top values accordingly
    sf::IntRect textureRect(x, y, 50, 50);

    // Set the texture rect for the sprite
    _sprite.setTextureRect(textureRect);
    _sprite.setTexture(_texture);

    sf::Vector2u size = {50,50};

    _sprite.setPosition(coordinates.y, coordinates.x);
    _sprite.setOrigin(size.x/2, size.x/2);


    window.get_window().draw(_sprite);
}