#include "VoidCell_v.h"

VoidCell_v::VoidCell_v(std::shared_ptr<VoidCell> void_cell_model) :
EntityView(void_cell_model){};

void VoidCell_v::update(const std::string& message_from_subject) {
    if (message_from_subject == "draw"){
        draw(0,0);
    }
}




void VoidCell_v::draw(int x, int y) {
    if(!_entity_model)
        return;

    sf::Vector2f coordinates = camera.cell_to_pixel(_entity_model->getPosition().getX(),
                                                    _entity_model->getPosition().getY(), 12, 20);

    _r_shape.setSize(sf::Vector2f(50, 50));
    _r_shape.setPosition(coordinates.y, coordinates.x);
    _r_shape.setOrigin(_r_shape.getSize().x/2 , _r_shape.getSize().y /2 );
    _r_shape.setFillColor(sf::Color::Black);
    window.get_window().draw(_r_shape);
}



