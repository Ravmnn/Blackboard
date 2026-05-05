#include <blackboard/editor/brush_cursor.hpp>

#include <algorithm>

#include <raymath.h>

#include <blackboard/editor/canvas.hpp>




void BrushCursor::update() noexcept
{
    const Vector2 mouse_position = brush.canvas.mouse_position();

    if (!brush.should_draw())
    {
        current_position_ = mouse_position;
        return;
    }

    const Vector2 direction = Vector2Normalize(mouse_position - current_position_);
    float distance = Vector2Distance(current_position_, mouse_position) / weight;

    const Vector2 velocity = direction * distance;

    current_position_ += velocity;
}




Vector2 BrushCursor::position() const noexcept
{
    return current_position_;
}