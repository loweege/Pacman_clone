#ifndef PACMANV0_RANDOM_H
#define PACMANV0_RANDOM_H
#include <iostream>
#include <random>
#include <unordered_set>

class Random {
private:
    std::mt19937 _mt;
    Random() : _mt(std::random_device{}()) {}
    static Random _instance;

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& instance() {
        return _instance;
    }

    template <typename Distribution>
    auto get_random() -> decltype(Distribution()(_mt)) {
        Distribution distribution;
        return distribution(_mt);
    }

    // Generate a random number within the specified range [min, max]
    template <typename T>
    T get_random_in_range(T min, T max) {
        std::uniform_int_distribution<T> distribution(min, max);
        std::random_device rd;
        std::mt19937 gen(rd());
        return distribution(gen);
    }


    Direction get_random_direction(const std::vector<Direction>& allowedDirections) {
        if (allowedDirections.empty()) {
            return Direction::None;
        }

        int max = allowedDirections.size() - 1;
        int directionIndex = get_random_in_range(0,max);

        return allowedDirections[directionIndex];
    }


};


#endif //PACMANV0_RANDOM_H