#ifndef PACMANV0_ENTITYVIEW_H
#define PACMANV0_ENTITYVIEW_H
#include "../../Game_logic/Observer/Observer.h"
#include "../../Game_logic/Observer/Subject.h"
#include "../../Game_logic/Entities/EntityModel.h"
#include "../Camera/Camera.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Window.h"


extern Camera camera;

class EntityView : public Observer{
public:

    Window& window  = Window::instance();
    EntityView(std::shared_ptr<EntityModel> entity_model);
    EntityView() = default;
    ~EntityView() override = default;

    void update(const std::string& message) override;

    //the draw changes based on the type of the entity
    virtual void draw(int x, int y) ;

protected:
    std::string _message;
    std::shared_ptr<EntityModel> _entity_model;
    sf::RectangleShape _r_shape;
    sf::Texture _texture;
    sf::Sprite _sprite;
};



#endif //PACMANV0_ENTITYVIEW_H