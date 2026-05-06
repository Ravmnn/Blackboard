#pragma once

#include <raylib.h>
#include <raymath.h>

#include <blackboard/updateable.hpp>




class Brush;


class BrushCursor : public Updateable
{
private:
    Vector2 last_position_ = {};
    Vector2 current_position_ = {};

    bool initialized_ = false;


public:
    const Brush& brush;
    float weight;


    explicit BrushCursor(const Brush& brush, const float weight) noexcept;


    void update() noexcept override;


    Vector2 position() const noexcept;
    Vector2 velocity() const noexcept { return current_position_ - last_position_; }


private:
    void initialize() noexcept;

    void update_position() noexcept;
};