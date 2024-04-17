#include "Game_logic/World.h"
#include "Game_logic/Entities/Ghost/Ghost.h"
#include "Game_representation/Game.h"


sf::Font g_font;
bool running{true};
int main() {
    g_font.loadFromFile("../Game_representation/States/Ranmor.ttf");
    Game game;
    game.run();
}
