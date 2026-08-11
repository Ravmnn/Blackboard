#pragma once

#include <chrono>




namespace bb
{




class Stopwatch
{
private:
    std::chrono::steady_clock::time_point start_ = std::chrono::steady_clock::now();


public:
    struct Elapsed
    {
        long ms;
        long ns;
    };




    [[nodiscard]] std::chrono::nanoseconds elapsed_ns() const noexcept {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_);
    }

    [[nodiscard]] std::chrono::milliseconds elapsed_ms() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_);
    }

    [[nodiscard]] std::chrono::seconds elapsed_secs() const noexcept {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_);
    }


    [[nodiscard]] Elapsed elapsed() const noexcept { return elapsed_from_ns(elapsed_ns().count()); }


    [[nodiscard]] static Elapsed elapsed_from_ns(const long nanoseconds) noexcept
    {
        const auto ns = std::chrono::nanoseconds(nanoseconds);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);
        const auto ns_remainder = ns - ms;

        return Elapsed{ .ms = ms.count(), .ns = ns_remainder.count() };
    }


    void reset() noexcept { start_ = std::chrono::steady_clock::now(); }
};




}