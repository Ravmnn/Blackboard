#include <blackboard/editor/tools/brush/brush.hpp>

#include <blackboard/editor/canvas.hpp>




Brush::Brush(Canvas& canvas, const float thickness) noexcept : Tool(canvas),
    stroke_({}, BLACK),
    thickness(thickness),
    cursor(2),
    body(*this),
    color_(canvas.palette.current_color())
{}




void Brush::update() noexcept
{
    if (got_inactive_)
        stroke_.points.clear();

    color_ = canvas_.palette.current_color();
    update_drawing_state();

    update_cursor();
    body.update();

    update_canvas_actions();

    current_thickness_ = thickness_from_speed();
    stroke_.color = color_;
    add_stroke_point();
}


void Brush::update_cursor() noexcept
{
    cursor.target_position = canvas_.mouse_position();
    cursor.immediate = !active();
    cursor.update();
}


void Brush::update_canvas_actions() noexcept
{
    if (got_inactive_)
        canvas_.add_stroke(stroke_);
}


void Brush::update_drawing_state() noexcept
{
    got_inactive_ = false;
    got_active_ = false;

    if (!was_active_ && active())
        got_active_ = true;

    if (was_active_ && !active())
        got_inactive_ = true;

    was_active_ = active();
}


void Brush::add_stroke_point() noexcept
{
    if (!active() || cursor.is_too_slow())
        return;

    stroke_.points.push_back(StrokePoint(cursor.position(), current_thickness_));
    modify_previous_points_thickness(current_thickness_);
}


void Brush::modify_previous_points_thickness(const float thickness) noexcept
{
    const int minimum_index = ((int)stroke_.points.size()) - point_thickness_back_iterating_amount_;

    for (int i = stroke_.points.size() - 1; i > minimum_index && i >= 0; i--)
        stroke_.points[i].thickness = thickness;

}




void Brush::draw() noexcept
{
    body.draw();
}