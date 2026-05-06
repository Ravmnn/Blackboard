#pragma once

#include <raylib.h>
#include <raymath.h>




class Interpolate
{
public:
    static float expolerp(const float start, const float target, const float smoothing, const float velocity = 1) noexcept
    {
        const float factor = 1.0f - powf(smoothing, GetFrameTime() * velocity);
        return lerp(start, target, factor);
    }


    static Vector2 expolerp(const Vector2& start, const Vector2& target, const float smoothing, const float velocity = 1) noexcept
    {
        return { expolerp(start.x, target.x, smoothing, velocity), expolerp(start.y, target.y, smoothing, velocity) };
    }


    static Color expolerp(const Color& start, const Color& target, const float smoothing, const float velocity = 1) noexcept
    {
        return {
            expolerp(start.r, target.r, smoothing, velocity),
            expolerp(start.g, target.g, smoothing, velocity),
            expolerp(start.b, target.b, smoothing, velocity),
            expolerp(start.a, target.a, smoothing, velocity)
        };
    }
};
