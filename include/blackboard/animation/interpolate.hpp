#pragma once

#include <cstdint>

#include <raylib.h>
#include <raymath.h>




namespace bb::animation
{




class Interpolate
{
public:
    static float expolerp(const float start, const float target, const float smoothing, const float speed = 1) noexcept
    {
        constexpr float Epsilon = 0.001f;
        const float factor = 1.0f - powf(smoothing, GetFrameTime() * speed);

        return std::abs(target - start) <= Epsilon ? target : lerp(start, target, factor);
    }


    static Vector2 expolerp(const Vector2& start, const Vector2& target, const float smoothing, const float speed = 1) noexcept
    {
        return {
            expolerp(start.x, target.x, smoothing, speed),
            expolerp(start.y, target.y, smoothing, speed)
        };
    }


    static Color expolerp(const Color& start, const Color& target, const float smoothing, const float speed = 1) noexcept
    {
        return {
            (uint8_t)std::round(expolerp(start.r, target.r, smoothing, speed)),
            (uint8_t)std::round(expolerp(start.g, target.g, smoothing, speed)),
            (uint8_t)std::round(expolerp(start.b, target.b, smoothing, speed)),
            (uint8_t)std::round(expolerp(start.a, target.a, smoothing, speed))
        };
    }




    static float linear(const float start, const float target, const float t) noexcept
    {
        return lerp(start, target, t);
    }


    static Vector2 linear(const Vector2& start, const Vector2& target, const float t) noexcept
    {
        return { linear(start.x, target.x, t), linear(start.y, target.y, t) };
    }


    static Color linear(const Color& start, const Color& target, const float t) noexcept
    {
        return {
            (uint8_t)std::round(linear(start.r, target.r, t)),
            (uint8_t)std::round(linear(start.g, target.g, t)),
            (uint8_t)std::round(linear(start.b, target.b, t)),
            (uint8_t)std::round(linear(start.a, target.a, t))
        };
    }
};




}