#pragma once

#include <concepts>
#include <optional>
#include <algorithm>

#include <raylib.h>

#include <blackboard/updateable.hpp>
#include <blackboard/vector.hpp>




namespace bb::animation
{




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

    bool immediate = false;


    Spring(const T& current, const T& target, const float damping = 0.6f, const float speed = 6) noexcept
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
        apply_min_max();

        constexpr float Epsilon = 0.01f;

        if (immediate || distance_of_current_to_target() <= Epsilon)
            current = target;
    }


private:
    void apply_min_max() noexcept
    {
        if (min.has_value())
            current = std::max(current, *min);

        if (max.has_value())
            current = std::min(current, *max);
    }


    [[nodiscard]] float distance_of_current_to_target() const noexcept;
};


template<> inline void Spring<Vector2>::apply_min_max() noexcept
{
    if (min.has_value())
        current = Vector2Max(current, *min);

    if (max.has_value())
        current = Vector2Min(current, *max);
}


template<> inline float Spring<float>::distance_of_current_to_target() const noexcept { return std::abs(target - current); }
template<> inline float Spring<Vector2>::distance_of_current_to_target() const noexcept { return std::abs(Vector2Length(target - current)); }




}