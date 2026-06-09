#pragma once

#include <chrono>
#include <iostream>






namespace bb
{




using Clock = std::chrono::steady_clock;
using Milliseconds = std::chrono::milliseconds;


class Timer
{
public:
    Clock::time_point start = Clock::now();


    void reset() noexcept { start = Clock::now(); }


    [[nodiscard]] double elapsed() const { return std::chrono::duration<double, std::milli>(Clock::now() - start).count(); }
};




class GlobalTimer
{
private:
    static Timer timer_;
    static std::string id_;


public:
    static void begin(const std::string& id = "") noexcept
    {
        id_ = id;
        timer_.reset();
    }

    static double end() noexcept { return timer_.elapsed(); }


    static void begin_log(const std::string& id = "") noexcept
    {
        begin(id);
        std::cout << "(begin) " << id_or_default() << std::endl;
    }

    static void end_log() noexcept
    {
        std::cout << "(end) " << id_or_default() << ": " << end() << "ms" << std::endl;
    }


private:
    static std::string id_or_default() noexcept { return id_.empty() ? "timer" : id_; }
};




}