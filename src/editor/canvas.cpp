#include <blackboard/editor/canvas.hpp>

#include <blackboard/editor/stroke_renderer.hpp>




Canvas::Canvas()
    : stroke_renderer_(8), brush(WHITE, 14)
{
    stroke_renderer_.should_debug_draw_points = true;
    stroke_renderer_.should_debug_draw_edges = true;
    stroke_renderer_.should_debug_draw_samples = true;
}




void Canvas::update() noexcept
{
    brush.update();

    if (brush.draw_finished())
        strokes.push_back(brush.stroke());

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        strokes.clear();
        brush.clear_stroke();
    }
}




void Canvas::draw() noexcept
{
    stroke_renderer_.draw_stroke(brush.stroke());

    for (auto& stroke : strokes)
        stroke_renderer_.draw_stroke(stroke);
}