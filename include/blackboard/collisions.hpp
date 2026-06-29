#pragma once

#include <raylib.h>
#include <raymath.h>




namespace bb
{




class Collisions
{
public:
    static bool point_inside_rectangle(const Vector2& point, const Rectangle& rectangle) noexcept
    {
        return point.x >= rectangle.x && point.x <= rectangle.x + rectangle.width &&
                point.y >= rectangle.y && point.y <= rectangle.y + rectangle.height;
    }


    static bool point_inside_circle(const Vector2& point, const Vector2& circle_center, const float radius) noexcept
    {
        return Vector2Distance(point, circle_center) <= radius;
    }
};




}