#include "Collectable_v.h"

Collectable_v::Collectable_v(std::shared_ptr<Collectable> collectable_model) : EntityView(collectable_model) {};

void Collectable_v::draw(int x, int y) {
    if(!_entity_model)
        return;

    sf::Vector2f coordinates = camera.cell_to_pixel(_entity_model->getPosition().getX(),
                                                    _entity_model->getPosition().getY(),
                                                    12, 20);

    _r_shape.setPosition(coordinates.y, coordinates.x);
    _r_shape.setOrigin(_r_shape.getSize().x/2 , _r_shape.getSize().y /2 );

    if(_entity_model->getType() == 2){
        _r_shape.setSize(sf::Vector2f(5, 5));
        _r_shape.setFillColor(sf::Color::Yellow);

    } else {



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

    }

    std::shared_ptr<Collectable> c = std::dynamic_pointer_cast<Collectable>(_entity_model);
    if (!c->get_is_eaten() && c->get_is_alive()){
        if (_entity_model->getType() == 2)
            window.get_window().draw(_r_shape);
        if (_entity_model->getType() == 4)
            window.get_window().draw(_sprite);
    }

}

void Collectable_v::update(const std::string &message) {
    if (message == "draw"){
        draw(595,0);
    }
}
