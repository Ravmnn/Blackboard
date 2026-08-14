#pragma once

#include <algorithm>

#include <raylib.h>




namespace bb::math
{




class Rect
{
public:
    static Rectangle from_position_and_size(const Vector2& position, const Vector2& size) noexcept
    {
        return { position.x, position.y, size.x, size.y };
    }


    static Rectangle from_two_points(const Vector2& start, const Vector2& end) noexcept
    {
        const float left = std::min(start.x, end.x);
        const float right = std::max(start.x, end.x);
        const float top = std::min(start.y, end.y);
        const float bottom = std::max(start.y, end.y);

        return { left, top, right - left, bottom - top };
    }




    static float get_corner_radius_from_normalized(const Vector2& size, const float normalized_radius) noexcept
    {
        return normalized_radius * std::min(size.x, size.y);
    }


    static float get_normalized_radius(const Vector2& size, const float radius) noexcept
    {
        return (radius * 2) / std::min(size.x, size.y);
    }
};




}