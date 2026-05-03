#include <blackboard/editor/canvas.hpp>

#include <blackboard/tween.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




Canvas::Canvas()
    : stroke_renderer_(12), canvas_camera_(0.05, 10, 0.3), brush(*this, WHITE, 14)
{
    stroke_renderer_.should_debug_draw_points = false;
    stroke_renderer_.should_debug_draw_edges = false;
    stroke_renderer_.should_debug_draw_samples = false;
}




void Canvas::update() noexcept
{
    canvas_camera_.update();
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
    BeginMode2D(canvas_camera_.camera());

    stroke_renderer_.draw_stroke(brush.stroke());

    for (auto& stroke : strokes)
        stroke_renderer_.draw_stroke(stroke);

    EndMode2D();
}