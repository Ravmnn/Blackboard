#pragma once

#include <cmath>

#include <chrono>




namespace bb
{




class Stopwatch
{
private:
    std::chrono::steady_clock::time_point start_ = std::chrono::steady_clock::now();


public:
    using MillisecondsDouble = std::chrono::duration<double, std::milli>;


    [[nodiscard]] std::chrono::nanoseconds elapsed_ns() const noexcept {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_);
    }

    [[nodiscard]] std::chrono::milliseconds elapsed_ms() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_);
    }

    [[nodiscard]] std::chrono::seconds elapsed_secs() const noexcept {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_);
    }


    [[nodiscard]] MillisecondsDouble elapsed_ms_double() const noexcept {
        return std::chrono::duration_cast<MillisecondsDouble>(std::chrono::steady_clock::now() - start_);
    }


    [[nodiscard]] static MillisecondsDouble ns_to_ms_double(const long nanoseconds) {
        return std::chrono::duration_cast<MillisecondsDouble>(std::chrono::nanoseconds(nanoseconds));
    }


    void reset() noexcept { start_ = std::chrono::steady_clock::now(); }
};




}