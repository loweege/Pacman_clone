#ifndef PACMANV0_GHOST_H
#define PACMANV0_GHOST_H
#include "../EntityModel.h"
#include "../../Utils/Random.h"

class Ghost : public EntityModel {
public:
    Ghost() = default;

    int getType() override;
    bool get_chasing_mode();
    void set_chasing_mode(bool chasing_mode);

    void respawn();

private:
    bool _chasing_mode = true;
    int _type = 3;
};


#endif //PACMANV0_GHOST_H