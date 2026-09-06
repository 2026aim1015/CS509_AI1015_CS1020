#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
    void start() {
        start_point = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_point = std::chrono::high_resolution_clock::now();
    }

    double elapsedMs() const {
        return std::chrono::duration<double, std::milli>(end_point - start_point).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_point;
    std::chrono::high_resolution_clock::time_point end_point;
};

#endif // TIMER_HPP