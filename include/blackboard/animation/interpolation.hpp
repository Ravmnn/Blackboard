#pragma once

#include <blackboard/animation/interpolate.hpp>
#include <blackboard/animation/animateable.hpp>




namespace bb::animation
{




template <typename T>
class ExponentialInterpolation : public Animateable<T>
{
public:
    using Animateable<T>::operator=;


    float speed, smoothing;


    ExponentialInterpolation() = default;
    ExponentialInterpolation(const T& current, const float speed, const float smoothing = 0.005f) noexcept : Animateable<T>(current),
        speed(speed), smoothing(smoothing) {}


    void update() noexcept override { this->current = Interpolate::expolerp(this->current, this->target, smoothing, speed); }
};




template <typename T>
class LinearInterpolation : public Animateable<T>
{
public:
    using Animateable<T>::operator=;


    float t;


    LinearInterpolation() = default;
    LinearInterpolation(const T& current, const float t) noexcept : Animateable<T>(current),
        t(t) {}


    void update() noexcept override { this->current = Interpolate::linear(this->current, this->target, t); }
};




}