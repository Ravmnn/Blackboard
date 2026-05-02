#include <blackboard/editor/brush.hpp>




void Brush::update() noexcept
{
    update_drawing_state();
    draw_current_segment();
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
    if (!should_draw_)
        return;

    if (draw_started_)
        stroke_.points.clear();

    stroke_.points.push_back(StrokePoint(GetMousePosition(), thickness));
}