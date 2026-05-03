#include <blackboard/editor/brush.hpp>

#include <algorithm>

#include <raymath.h>




void Brush::update() noexcept
{
    update_drawing_state();
    brush_cursor.update();

    update_smooth_velocity();
    draw_current_segment();
}


void Brush::update_smooth_velocity() noexcept
{
    if (!should_draw_)
    {
        smooth_velocity_ = 0;
        return;
    }

    if (!is_too_slow())
        smooth_velocity_ += (current_velocity() - smooth_velocity_) * velocity_smoothing_;
}


void Brush::update_drawing_state() noexcept
{
    draw_finished_ = false;
    draw_started_ = false;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        should_draw_ = true;
        draw_started_ = true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        should_draw_ = false;
        draw_finished_ = true;
    }
}


void Brush::draw_current_segment() noexcept
{
    if (draw_started_)
        stroke_.points.clear();

    if (!should_draw_ || is_too_slow())
        return;

    const float thickness = thickness_from_velocity();
    stroke_.points.push_back(StrokePoint(brush_cursor.position(), thickness));

    modify_previous_points_thickness(thickness);
}


void Brush::modify_previous_points_thickness(const float thickness) noexcept
{
    for (int i = stroke_.points.size() - 1; i > ((int)stroke_.points.size()) - point_thickness_back_iterating_amount_; i--)
    {
        if (i < 0)
            break;

        stroke_.points[i].thickness = thickness;
    }
}




float Brush::current_velocity() const noexcept
{
    if (stroke_.points.empty() || draw_started_)
        return 0;

    return Vector2Length(brush_cursor.position() - stroke_.points.back().position) / GetFrameTime();
}




float Brush::thickness_from_velocity() const noexcept
{
    const float t = std::clamp(smooth_velocity_ / max_velocity_, 0.0f, 1.0f);
    return max_thickness() + t * (min_thickness() - max_thickness());
}




bool Brush::is_too_slow() const noexcept
{
    const float velocity = current_velocity();
    return !stroke_.points.empty() && velocity < 0.01;
}