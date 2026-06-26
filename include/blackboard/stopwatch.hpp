#pragma once

#include <chrono>




namespace bb
{




class Stopwatch
{
private:
    std::chrono::steady_clock::time_point start_ = std::chrono::steady_clock::now();


public:
    [[nodiscard]] std::chrono::milliseconds elapsed_ms() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_);
    }

    [[nodiscard]] std::chrono::seconds elapsed_secs() const noexcept {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_);
    }


    void reset() noexcept { start_ = std::chrono::steady_clock::now(); }
};




}