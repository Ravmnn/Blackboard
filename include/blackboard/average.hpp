#pragma once

#include <cassert>

#include <deque>
#include <optional>

#include <blackboard/stopwatch.hpp>




namespace bb
{




class Average
{
private:
    std::deque<float> values_;

    std::optional<float> last_delayed_value_;
    Stopwatch stopwatch_;


public:
    size_t samples;
    float delay_secs = 1;


    Average(const size_t samples = 32) noexcept : samples(samples) {}


    void add(const float value) noexcept
    {
        if (values_.size() >= samples)
            values_.pop_front();

        values_.push_back(value);

        if (!last_delayed_value_)
            last_delayed_value_ = value;
    }


    [[nodiscard]] float get() noexcept
    {
        assert(last_delayed_value_);
        update_last_delayed_value(calculate_average());
        return *last_delayed_value_;
    }


    [[nodiscard]] bool is_sampling() const noexcept { return values_.size() < samples; }
    [[nodiscard]] bool delay_time_reached() const noexcept { return (float)stopwatch_.elapsed_secs().count() >= delay_secs; }


private:
    [[nodiscard]] float calculate_average() const noexcept
    {
        float accumulator = 0;

        for (const auto& value : values_)
            accumulator += value;

        return accumulator;
    }


    void update_last_delayed_value(const float accumulator) noexcept
    {
        if (!delay_time_reached())
            return;

        stopwatch_.reset();
        last_delayed_value_ = accumulator / (float)values_.size();
    }
};




}