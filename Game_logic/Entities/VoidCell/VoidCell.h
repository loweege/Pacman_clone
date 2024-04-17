#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_H
#include "../EntityModel.h"

class VoidCell : public EntityModel{
public:
    VoidCell() = default;

    int getType() override;

private:
    int _type = 6;
};




#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_VOIDCELL_H
