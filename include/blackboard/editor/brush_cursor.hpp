#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>




class Brush;


class BrushCursor : public Updateable
{
private:
    Vector2 current_position_ = {};


public:
    const Brush& brush;
    float weight;


    explicit BrushCursor(const Brush& brush, const float weight)
        : brush(brush), weight(weight) {}


    void update() noexcept override;


    Vector2 position() const noexcept;
};