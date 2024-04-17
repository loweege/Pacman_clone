#include "Ghost_v.h"


Ghost_v::Ghost_v(std::shared_ptr<Ghost> entity_ghost) :  EntityView(entity_ghost){};

void Ghost_v::update(const std::string& message_from_subject) {
    std::shared_ptr<Ghost> g = std::dynamic_pointer_cast<Ghost>(_entity_model);

    if (message_from_subject == "draw") {

        if (g->get_chasing_mode()){

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
                    draw(650, 195);
                } else {
                    draw(650, 245);
                }

            }

            if (_entity_model->getDirection() == Direction::Up) {
                // draw(650, 295);


                // Get the current time
                sf::Time current_time = _clock.getElapsedTime();

                // Calculate the time since the start
                sf::Time elapsed_time = current_time - _start_time;

                // Calculate the index of the current 0.5-second interval
                int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

                // Toggle between two positions every 0.5 seconds
                if (intervalIndex % 2 == 0) {
                    draw(650, 295);
                } else {
                    draw(650, 345);
                }

            }
            if (_entity_model->getDirection() == Direction::Down) {
                //draw(645, 145);


                // Get the current time
                sf::Time current_time = _clock.getElapsedTime();

                // Calculate the time since the start
                sf::Time elapsed_time = current_time - _start_time;

                // Calculate the index of the current 0.5-second interval
                int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

                // Toggle between two positions every 0.5 seconds
                if (intervalIndex % 2 == 0) {
                    draw(650, 95);
                } else {
                    draw(650, 145);
                }

            }
            if (_entity_model->getDirection() == Direction::Right) {
                //draw(650, 95);


                // Get the current time
                sf::Time current_time = _clock.getElapsedTime();

                // Calculate the time since the start
                sf::Time elapsed_time = current_time - _start_time;

                // Calculate the index of the current 0.5-second interval
                int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

                // Toggle between two positions every 0.5 seconds
                if (intervalIndex % 2 == 0) {
                    draw(650, 0);
                } else {
                    draw(650, 50);
                }

            }


        } else {
           // draw(0,495);
            sf::Time current_time = _clock.getElapsedTime();

            // Calculate the time since the start
            sf::Time elapsed_time = current_time - _start_time;

            // Calculate the index of the current 0.5-second interval
            int intervalIndex = static_cast<int>(elapsed_time.asSeconds() / 0.25);

            // Toggle between two positions every 0.5 seconds
            if (intervalIndex % 2 == 0) {
                draw(0, 595);
            } else {
                draw(50, 595);
            }
        }



    }
}


void Ghost_v::draw(int x, int y) {
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