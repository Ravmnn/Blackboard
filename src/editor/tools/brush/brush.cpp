#include <blackboard/editor/tools/brush/brush.hpp>

#include <blackboard/editor/canvas.hpp>




using bb::editor::Brush;




Brush::Brush(Canvas& canvas, const float thickness) noexcept : Tool(canvas),
    stroke_({}, BLACK),
    color_(canvas.palette.current_color()),
    thickness(thickness),
    cursor(2),
    body(*this)
{}




void Brush::update() noexcept
{
    if (got_inactive_)
        stroke_.points.clear();

    Tool::update();

    color_ = canvas_.palette.current_color();

    update_cursor();
    update_canvas_actions();

    body.update();

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


void Brush::add_stroke_point() noexcept
{
    if (!active() || cursor.is_too_slow())
        return;

    stroke_.points.emplace_back(cursor.position(), current_thickness_);
    modify_previous_points_thickness(current_thickness_);
}


void Brush::modify_previous_points_thickness(const float thickness) noexcept
{
    const int minimum_index = ((int)stroke_.points.size()) - point_thickness_back_iterating_amount_;

    for (int i = (int)stroke_.points.size() - 1; i > minimum_index && i >= 0; i--)
        stroke_.points[i].thickness = thickness;

}




void Brush::draw() noexcept
{
    body.draw();
}