#ifndef PACMANV0_CAMERA_H
#define PACMANV0_CAMERA_H
#include "SFML/Graphics.hpp"

class Camera {
public:
    Camera(int window_width, int window_height)
            : _window_width{window_width}, _window_height{window_height}{};

    sf::Vector2f cell_to_pixel(float x, float y, int rows, int columns) const {
        return sf::Vector2f(((float) x * _window_height / rows) + 25,
                            ((float) y * _window_width / columns) + 25);
    }


private:
    int _window_width, _window_height;

};

#endif //PACMANV0_CAMERA_H
