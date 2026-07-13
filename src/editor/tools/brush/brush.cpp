#include <blackboard/editor/tools/brush/brush.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::Brush,
    bb::editor::StrokePoint;




Brush::Brush(EditorEnvironment& environment, const float thickness) noexcept : Tool(environment),
    stroke_({}),
    color_(environment.editor.palette.current_color()),
    thickness(thickness),
    cursor(2),
    body(*this)
{}




void Brush::update() noexcept
{
    if (got_inactive_)
        stroke_.points.clear();

    Tool::update();

    color_ = editor().palette.current_color();

    update_cursor();
    update_canvas_actions();

    body.update();

    current_thickness_ = thickness_from_speed();
    add_stroke_point();
}


void Brush::update_cursor() noexcept
{
    cursor.target_position = editor().canvas.mouse_position();
    cursor.immediate = !active();
    cursor.update();
}


void Brush::update_canvas_actions() noexcept
{
    if (got_inactive_)
        editor().stroke_manager.add_stroke(stroke_);
}


void Brush::add_stroke_point() noexcept
{
    if (!active() || cursor.is_too_slow())
        return;

    stroke_.points.push_back(create_stroke_point());
    modify_previous_points_thickness(current_thickness_);
}


void Brush::modify_previous_points_thickness(const float thickness) noexcept
{
    const int minimum_index = ((int)stroke_.points.size()) - point_thickness_back_iterating_amount_;

    for (int i = (int)stroke_.points.size() - 1; i > minimum_index && i >= 0; i--)
        stroke_.points[i].thickness = thickness;
}


StrokePoint Brush::create_stroke_point() const noexcept
{
    return StrokePoint{
        .position = cursor.position(),
        .thickness = current_thickness_,
        .color = color_
    };
}




void Brush::draw() noexcept
{
    if (!draw_finished())
        editor().stroke_manager.draw_stroke(stroke_);

    body.draw();
}




Vector2 Brush::position() const noexcept
{
    return active() ? cursor.position() : editor().canvas.mouse_position();
}