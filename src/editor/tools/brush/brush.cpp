#include <blackboard/editor/tools/brush/brush.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::Brush;




Brush::Brush(Editor& editor, const float thickness) noexcept : Tool(editor),
    stroke_({}, BLACK),
    color_(editor_.palette.current_color()),
    thickness(thickness),
    cursor(2),
    body(*this)
{}




void Brush::update() noexcept
{
    if (got_inactive_)
        stroke_.points.clear();

    Tool::update();

    color_ = editor_.palette.current_color();

    update_cursor();
    update_canvas_actions();

    body.update();

    current_thickness_ = thickness_from_speed();
    stroke_.color = color_;
    add_stroke_point();
}


void Brush::update_cursor() noexcept
{
    cursor.target_position = editor_.canvas.mouse_position();
    cursor.immediate = !active();
    cursor.update();
}


void Brush::update_canvas_actions() noexcept
{
    if (got_inactive_)
        editor_.canvas.add_stroke(stroke_);
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
    if (!draw_finished())
        editor_.canvas.stroke_renderer.draw_stroke(stroke());

    body.draw();
}