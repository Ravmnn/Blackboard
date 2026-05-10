#include <blackboard/editor/lazy_cursor.hpp>

#include <algorithm>

#include <raymath.h>




LazyCursor::LazyCursor(const float laziness) noexcept
    : laziness(laziness)
{}




void LazyCursor::update() noexcept
{
    if (!initialized_)
        initialize();

    update_position();
}


void LazyCursor::initialize() noexcept
{
    last_position_ = current_position_ = target_position;

    initialized_ = true;
}


void LazyCursor::update_position() noexcept
{
    last_position_ = current_position_;

    if (immediate)
        current_position_ = target_position;

    const Vector2 direction = Vector2Normalize(target_position - current_position_);
    const float distance = Vector2Distance(current_position_, target_position) / laziness;

    current_position_ += direction * distance;
}




Vector2 LazyCursor::position() const noexcept
{
    return current_position_;
}