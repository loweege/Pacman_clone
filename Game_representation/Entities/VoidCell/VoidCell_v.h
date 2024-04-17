#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_V_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_V_H
#include "../EntityView.h"
#include "../../../Game_logic/Entities/VoidCell/VoidCell.h"

class VoidCell_v : public EntityView{
public:
    VoidCell_v() = default;
    VoidCell_v(std::shared_ptr<VoidCell> void_cell_model);
    void update(const std::string& message) override;
    void draw(int x, int y) override;
};


#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_V_H
