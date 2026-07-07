#pragma once

#include <algorithm>

#include <raymath.h>




namespace bb::math
{




class Segment
{
public:
    static bool is_point_in_segment(const Vector2& start, const Vector2& end, const Vector2& point, const float half_thickness = 1)
    {
        return distance_to_segment(start, end, point) <= half_thickness;
    }


    static float distance_to_segment(const Vector2& start, const Vector2& end, const Vector2& point) noexcept
    {
        const Vector2 ab = Vector2Subtract(end, start);
        const Vector2 ap = Vector2Subtract(point, start);

        const float ab_len_sq = Vector2DotProduct(ab, ab);

        if (ab_len_sq == 0.0f)
            return Vector2Distance(point, start);

        float t = Vector2DotProduct(ap, ab) / ab_len_sq;

        t = std::clamp(t, 0.0f, 1.0f);

        const Vector2 closest = {
            start.x + ab.x * t,
            start.y + ab.y * t
        };

        return Vector2Distance(point, closest);
    }
};




}