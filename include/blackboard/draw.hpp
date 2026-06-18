#pragma once

#include <raylib.h>




namespace bb
{




class Draw
{
public:
    static void stretched_ellipse(const Vector2& position, const float radius, const float stretch, const Color& color = WHITE) noexcept
    {
        DrawEllipse(
            (int)position.x, (int)position.y,
            radius + stretch, radius,
            color
        );
    }
};




}