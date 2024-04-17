#ifndef PACMANV0_STOPWATCH_H
#define PACMANV0_STOPWATCH_H
#include <iostream>
#include "chrono"

class Stopwatch{
public:
    static Stopwatch& get_instance() {
        static Stopwatch istance;
        return istance;
    }

    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    inline double deltatime() {
        TimePoint actual_time = Clock::now();

        std::chrono::duration<double> duration = actual_time - _previous_time;
        _previous_time = actual_time;

        return duration.count();
    }

private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint _previous_time;

    Stopwatch() {
        _previous_time = Clock::now();
    }

};


#endif //PACMANV0_STOPWATCH_H