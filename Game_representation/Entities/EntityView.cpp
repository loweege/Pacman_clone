#include "EntityView.h"

EntityView::EntityView(std::shared_ptr<EntityModel> entity_model)
: _entity_model{entity_model}{

}


void EntityView::update(const std::string& message) {
    if (message == "draw"){
        draw(0,0);
    }
}

void EntityView::draw(int x, int y) {}