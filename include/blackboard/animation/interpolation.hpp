#pragma once

#include <blackboard/updateable.hpp>

#include <blackboard/animation/interpolate.hpp>




template <typename T>
class Interpolation : public Updateable
{
public:
    T current, target;
    float speed, smoothing;


    Interpolation() = default;
    Interpolation(const T& current, const float speed, const float smoothing = 0.005f) noexcept
        : current(current), target(current), speed(speed), smoothing(smoothing) {}


    operator T() const noexcept { return current; }


    void update() noexcept override { current = Interpolate::expolerp(current, target, smoothing, speed); }


    void set_value_immediately(const T& value) noexcept { current = target = value; }

    T& set_target_and_update(const T& target) noexcept
    {
        this->target = target;
        update();

        return current;
    }
};