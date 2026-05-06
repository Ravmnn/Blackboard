#pragma once

#include <concepts>
#include <optional>
#include <algorithm>

#include <raylib.h>

#include <blackboard/updateable.hpp>




template <typename T> concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};


template <typename T> requires Arithmetic<T>
class Spring : public Updateable
{
public:
    T current, target;
    T velocity = {};

    std::optional<T> max, min;

    float damping;
    float speed;


    Spring(const T& current, const T& target, const float damping, const float speed) noexcept
        : current(current), target(target), damping(damping), speed(speed) {}


    operator T() const noexcept { return current; }

    T operator =(const T& value) noexcept { return target = value; }


    void update() noexcept override
    {
        const float dt = GetFrameTime();

        const float omega = speed;
        const float zeta = damping;

        const float omega_squared = omega * omega;
        const float dt_omega_squared = dt * omega_squared;
        const float dt2_omega_squared = dt * dt_omega_squared;
        const float f = 1.0f + 2.0f * dt * omega * zeta;
        const float inverse_determinant = 1.0f / (f + dt2_omega_squared);

        const T new_value = (current * f + velocity * dt + target * dt2_omega_squared) * inverse_determinant;
        const T new_velocity = (velocity + (target - current) * dt_omega_squared) * inverse_determinant;

        current = new_value;
        velocity = new_velocity;

        clamp_current();
    }


    void clamp_current() noexcept
    {
        if (min.has_value())
            current = std::max(current, *min);

        if (max.has_value())
            current = std::min(current, *max);
    }
};