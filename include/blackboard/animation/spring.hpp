#pragma once

#include <optional>

#include <raylib.h>

#include <blackboard/animation/animateable.hpp>




namespace bb::animation
{




template <typename T>
class Spring : public Animateable<T>
{
public:
    using Animateable<T>::operator=;


    std::optional<T> max, min;

    T velocity = {};

    float damping;
    float speed;


    explicit Spring(const T& current, const float damping = 0.6f, const float speed = 6) noexcept : Animateable<T>(current),
        damping(damping), speed(speed) {}


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

        const T new_value = (this->current * f + velocity * dt + this->target * dt2_omega_squared) * inverse_determinant;
        const T new_velocity = (velocity + (this->target - this->current) * dt_omega_squared) * inverse_determinant;

        this->current = new_value;
        velocity = new_velocity;

        clamp_current();
    }


    void set_value_immediately(const T& value) noexcept override { Animateable<T>::set_value_immediately(value); velocity = {}; }


protected:
    void clamp_current() noexcept
    {
        apply_min_max();

        constexpr float Epsilon = 0.01f;

        if (this->immediate || distance_of_current_to_target() <= Epsilon)
            this->current = this->target;
    }


    void apply_min_max() noexcept
    {
        if (min.has_value()) this->current = std::max(this->current, *min);
        if (max.has_value()) this->current = std::min(this->current, *max);
    }


    [[nodiscard]] float distance_of_current_to_target() const noexcept { return std::abs(this->target - this->current); }
};


template<> inline void Spring<Vector2>::apply_min_max() noexcept
{
    if (min.has_value()) current = Vector2Max(current, *min);
    if (max.has_value()) current = Vector2Min(current, *max);
}


template<> inline float Spring<Vector2>::distance_of_current_to_target() const noexcept { return std::abs(Vector2Length(target - current)); }




}