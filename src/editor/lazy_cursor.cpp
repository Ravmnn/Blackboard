#include <blackboard/editor/lazy_cursor.hpp>

#include <raymath.h>




using bb::editor::LazyCursor;




LazyCursor::LazyCursor(const float laziness) noexcept
    : laziness(laziness)
{}




void LazyCursor::update() noexcept
{
    if (!initialized_)
        initialize();

    update_position();
    update_smooth_velocity();
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


void LazyCursor::update_smooth_velocity() noexcept
{
    if (immediate)
    {
        smooth_speed_ = 0;
        return;
    }

    if (!is_too_slow())
        smooth_speed_ += (current_speed() - smooth_speed_) * speed_smoothing;
}