#pragma once

#include <blackboard/updateable.hpp>

#include <blackboard/animation/interpolate.hpp>




template <typename T>
class Interpolation : public Updateable
{
public:
    T current, target;
    float smoothing, velocity;


    Interpolation() = default;
    Interpolation(const T& current, const float velocity, const float smoothing = 0.005f) noexcept
        : current(current), target(current), velocity(velocity), smoothing(smoothing) {}


    operator T() const noexcept { return current; }


    void update() noexcept override { current = Interpolate::expolerp(current, target, smoothing, velocity); }


    T& set_target_and_update(const T& target) noexcept
    {
        this->target = target;
        update();

        return current;
    }
};