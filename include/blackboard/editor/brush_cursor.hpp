#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>




class Brush;


class BrushCursor : public Updateable
{
private:
    const Brush& brush_;
    Vector2 current_position_ = {};


public:
    float weight;


    explicit BrushCursor(const Brush& brush, const float weight)
        : brush_(brush), weight(weight) {}


    void update() noexcept override;


    const Vector2& position() const noexcept { return current_position_; }
};