#pragma once

#include <raylib.h>
#include <raymath.h>




namespace bb
{




class Bounds
{
public:
    [[nodiscard]] virtual Rectangle bounding_box() const noexcept = 0;


    [[nodiscard]] Vector2 box_position() const noexcept
    {
        const Rectangle box = bounding_box();
        return { box.x, box.y };
    }

    [[nodiscard]] Vector2 box_size() const noexcept
    {
        const Rectangle box = bounding_box();
        return { box.width, box.height };
    }

    [[nodiscard]] Vector2 box_center() const noexcept
    {
        return box_position() + box_size() / 2;
    }
};




}