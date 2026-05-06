#include <blackboard/editor/tools/brush_cursor.hpp>

#include <algorithm>

#include <raymath.h>

#include <blackboard/editor/canvas.hpp>




BrushCursor::BrushCursor(const Brush& brush, const float weight) noexcept
    : brush(brush), weight(weight)
{}




void BrushCursor::update() noexcept
{
    if (!initialized_)
        initialize();

    update_position();
}


void BrushCursor::initialize() noexcept
{
    last_position_ = current_position_ = brush.canvas().mouse_position();

    initialized_ = true;
}


void BrushCursor::update_position() noexcept
{
    last_position_ = current_position_;

    const Vector2 mouse_position = brush.canvas().mouse_position();

    if (!brush.should_draw())
        current_position_ = mouse_position;

    const Vector2 direction = Vector2Normalize(mouse_position - current_position_);
    const float distance = Vector2Distance(current_position_, mouse_position) / weight;

    current_position_ += direction * distance;
}




Vector2 BrushCursor::position() const noexcept
{
    return current_position_;
}