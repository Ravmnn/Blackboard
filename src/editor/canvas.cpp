#include <blackboard/editor/canvas.hpp>




using bb::editor::Canvas;




Canvas::Canvas() noexcept :
    canvas_renderer(*this),
    camera(*this, 0.2, 25, 0.13),

    stroke_mesh_generator(6),
    stroke_renderer(&stroke_mesh_generator, &camera),

    background_color(BLACK, 0.6)
{
    stroke_renderer.should_debug_draw_points = false;
    stroke_renderer.should_debug_draw_edges = false;
    stroke_renderer.should_debug_draw_samples = false;
    stroke_renderer.should_debug_draw_caps = false;

    camera.bounds_expansion = { 100, 100 };
}




void Canvas::update() noexcept
{
    camera.update();
    canvas_renderer.update();
}




void Canvas::draw_strokes() noexcept
{
    for (const auto& mesh : stroke_meshes)
        stroke_renderer.draw_stroke_mesh(*mesh);
}




void Canvas::add_stroke(const Stroke& stroke) noexcept
{
    if (stroke.points.empty())
        return;

    stroke_meshes.push_back(stroke_mesh_generator.generate_mesh(stroke));
}