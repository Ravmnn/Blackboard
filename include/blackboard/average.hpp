#pragma once

#include <deque>




namespace bb
{




class Average
{
private:
    std::deque<float> values_;


public:
    size_t samples;


    Average(const size_t samples = 32) noexcept : samples(samples) {}


    void add(const float value) noexcept
    {
        if (values_.size() >= 32)
            values_.pop_front();

        values_.push_back(value);
    }


    [[nodiscard]] float get() const noexcept
    {
        float accumulator = 0;

        for (const auto& value : values_)
            accumulator += value;

        return accumulator / (float)values_.size();
    }


    [[nodiscard]] bool is_sampling() const noexcept { return values_.size() < samples; }
};




}