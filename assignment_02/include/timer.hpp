#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>

//measure exact execution time

class Timer{
    public:
    void start(){
        start_ = std::chrono::high_resolution_clock::now();
    }

    void stop(){
        end_ =std::chrono::high_resolution_clock::now();
    
    }

    double elapsedMs() const{
        return std::chrono::duration<double, std::milli>(end_ - start_).count();
    }

    private:
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;
};
#endif