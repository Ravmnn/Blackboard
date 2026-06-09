#pragma once

#include <raylib.h>






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
};




}