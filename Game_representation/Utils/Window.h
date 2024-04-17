#ifndef INC_2023_PROJECT_LOWEEGEEBELGIUM_WINDOW_H
#define INC_2023_PROJECT_LOWEEGEEBELGIUM_WINDOW_H
#include "SFML/Graphics.hpp"


class Window{
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    static Window& instance() {
        static Window instance;
        return instance;
    }

    sf::RenderWindow& get_window() {
        return _window;
    }

    int get_window_width(){
        return _window_width;
    }

    int get_window_height(){
        return _window_height;
    }

private:
    sf::RenderWindow _window;
    int _window_width = 1000;
    int _window_height = 600;

    Window() : _window(sf::VideoMode(1000, 600), "Pacman"){};

};
extern Window& window;
#endif //INC_2023_PROJECT_LOWEEGEEBELGIUM_WINDOW_H
