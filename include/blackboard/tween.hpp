#pragma once

#include <math.h>

#include <raylib.h>




class Tween
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
};