#pragma once

#include <blackboard/updateable.hpp>

#include <blackboard/animation/interpolate.hpp>




template <typename T>
class Interpolation : public Updateable
{
public:
    T current, target;


    Interpolation() = default;
    Interpolation(const T& current) noexcept
        : current(current), target(current) {}


    operator T() const noexcept { return current; }

    T operator =(const T& value) noexcept { return target = value; }


    void set_value_immediately(const T& value) noexcept { current = target = value; }

    T& set_target_and_update(const T& target) noexcept
    {
        this->target = target;
        update();

        return current;
    }
};




template <typename T>
class ExponentialInterpolation : public Interpolation<T>
{
public:
    using Interpolation<T>::operator=;


    float speed, smoothing;


    ExponentialInterpolation() = default;
    ExponentialInterpolation(const T& current, const float speed, const float smoothing = 0.005f) noexcept : Interpolation<T>(current),
        speed(speed), smoothing(smoothing) {}


    void update() noexcept override { this->current = Interpolate::expolerp(this->current, this->target, smoothing, speed); }
};




template <typename T>
class LinearInterpolation : public Interpolation<T>
{
public:
    using Interpolation<T>::operator=;


    float t;


    LinearInterpolation() = default;
    LinearInterpolation(const T& current, const float t) noexcept : Interpolation<T>(current),
        t(t) {}


    void update() noexcept override { this->current = Interpolate::linear(this->current, this->target, t); }
};