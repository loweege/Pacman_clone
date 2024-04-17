#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_SCORE_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_SCORE_H
#include "../Observer/Observer.h"
#include "iostream"
#include <memory>

class Score : public Observer{

public:
    unsigned int                current_level {0};
    Score() = default;
    ~Score() override = default;
    void update(const std::string &message) override;

    void coin_score();
    void fruit_score();
    void ghost_score();
    void level_finished_score();
    inline void             reset() { _score = 0; _life_left = 3; _collected_coins = 0; }
    inline bool             is_game_over() const { return _life_left == 0; }
    inline bool             is_victory() {
        if(_collected_coins == 99){
            _collected_coins = 0;
            return true;}
        else{
            return false;
        }
    }
    inline int get_lifes(){return _life_left;}
    int get_score();


private:
    int _score = 0;
    int _collected_coins {0};
    int _life_left{3};
};

extern std::shared_ptr<Score> score_m;

#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_SCORE_H
