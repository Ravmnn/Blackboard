#pragma once

#include <algorithm>

#include <raymath.h>




namespace bb::math
{




class Segment
{
public:
    Vector2 start;
    Vector2 end;




    static bool intersects(const Segment& a, const Segment& b) noexcept
    {
        const float o1 = orientation(a, b.start);
        const float o2 = orientation(a, b.end);
        const float o3 = orientation(b, a.start);
        const float o4 = orientation(b, a.end);

        if ((o1 > 0) != (o2 > 0) && (o3 > 0) != (o4 > 0))
            return true;

        if (o1 == 0 && point_on_segment(a, b.start)) return true;
        if (o2 == 0 && point_on_segment(a, b.end)) return true;
        if (o3 == 0 && point_on_segment(b, a.start)) return true;
        if (o4 == 0 && point_on_segment(b, a.end)) return true;

        return false;
    }


    static bool is_point_in_segment(const Segment& segment, const Vector2& point, const float half_thickness = 1) noexcept
    {
        return distance_to_segment(segment, point) <= half_thickness;
    }


    static float distance_to_segment(const Segment& segment, const Vector2& point) noexcept
    {
        const Vector2 ab = Vector2Subtract(segment.end, segment.start);
        const Vector2 ap = Vector2Subtract(point, segment.start);

        const float ab_len_sq = Vector2DotProduct(ab, ab);

        if (ab_len_sq == 0.0f)
            return Vector2Distance(point, segment.start);

        float t = Vector2DotProduct(ap, ab) / ab_len_sq;

        t = std::clamp(t, 0.0f, 1.0f);

        const Vector2 closest = {
            segment.start.x + ab.x * t,
            segment.start.y + ab.y * t
        };

        return Vector2Distance(point, closest);
    }


private:
    static float orientation(const Segment& segment, const Vector2& point) noexcept
    {
        return (segment.end.x - segment.start.x) * (point.y - segment.start.y)
                - (segment.end.y - segment.start.y) * (point.x - segment.start.x);
    }


    static bool point_on_segment(const Segment& segment, const Vector2& point) noexcept
    {
        return point.x >= std::min(segment.start.x, segment.end.x) &&
            point.x <= std::max(segment.start.x, segment.end.x) &&
            point.y >= std::min(segment.start.y, segment.end.y) &&
            point.y <= std::max(segment.start.y, segment.end.y);
    }
};




}