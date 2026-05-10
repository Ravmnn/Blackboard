#include <blackboard/editor/tools/brush/brush.hpp>

#include <algorithm>
#include <string>

#include <raymath.h>

#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/canvas.hpp>




Brush::Brush(Canvas& canvas, const Color& color, const float thickness) noexcept : Tool(canvas),
    stroke_({}, color),
    cursor(2),
    body(*this),
    color(color),
    thickness(thickness)
{}




void Brush::update() noexcept
{
    if (draw_finished_)
        stroke_.points.clear();

    update_drawing_state();

    update_cursor();
    body.update();

    update_canvas_actions();
    update_smooth_velocity();

    current_thickness_ = thickness_from_velocity();
    add_stroke_point();
}


void Brush::update_cursor() noexcept
{
    cursor.target_position = canvas_.mouse_position();
    cursor.immediate = !should_draw_;
    cursor.update();
}


void Brush::update_canvas_actions() noexcept
{
    if (draw_finished_)
        canvas_.add_stroke(stroke_);
}


void Brush::update_smooth_velocity() noexcept
{
    if (!should_draw_)
    {
        smooth_velocity_ = 0;
        return;
    }

    // TODO: moving this to LazyCursor maybe?
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


void Brush::add_stroke_point() noexcept
{
    if (!should_draw_ || is_too_slow())
        return;

    stroke_.points.push_back(StrokePoint(cursor.position(), current_thickness_));
    modify_previous_points_thickness(current_thickness_);
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




void Brush::draw() noexcept
{
    body.draw();
}




float Brush::current_velocity() const noexcept
{
    if (stroke_.points.empty() || draw_started_)
        return 0;

    const float velocity = Vector2Distance(cursor.position(), stroke_.points.back().position);
    return std::min(velocity, max_velocity_);
}




float Brush::thickness_from_velocity() const noexcept
{
    const float t = std::clamp(smooth_velocity_ / max_smooth_velocity_, 0.0f, 1.0f);
    return max_thickness() + t * (min_thickness() - max_thickness());
}




bool Brush::is_too_slow() const noexcept
{
    const float velocity = current_velocity();
    return !stroke_.points.empty() && velocity < 1;
}