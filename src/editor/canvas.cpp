#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




using bb::editor::Canvas,
    bb::rendering::WindowRenderer,
    bb::rendering::TextureRenderer;




Canvas::Canvas(const Palette& palette) :
    background_color_(DefaultBackgroundColor, 0.6),

    canvas_renderer(*this),
    camera(*this, 0.2, 25, 0.13),

    stroke_mesh_generator(6),
    stroke_renderer(stroke_mesh_generator, &camera),

    palette(palette),

    brush(*this, 14),
    eraser(*this)
{
    stroke_renderer.should_debug_draw_points = false;
    stroke_renderer.should_debug_draw_edges = false;
    stroke_renderer.should_debug_draw_samples = false;
    stroke_renderer.should_debug_draw_caps = false;

    camera.bounds_expansion = { 100, 100 };

    current_tool = &brush;
}




void Canvas::update() noexcept
{
    update_background_color();
    camera.update();
    current_tool->update();

    canvas_renderer.update();
}



void Canvas::update_background_color() noexcept
{
    if (dynamic_background_color)
        background_color_ = palette.background_color_from_current();
    else
        background_color_ = DefaultBackgroundColor;

    background_color_.update();
}



void Canvas::draw() noexcept
{
    canvas_renderer.begin_render();
        draw_content();
    canvas_renderer.end_render();

    canvas_renderer.draw_contents_texture();
}


void Canvas::draw_content() noexcept
{
    camera.enable();
        draw_strokes();
        current_tool->draw();
    camera.disable();
}



void Canvas::draw_strokes() noexcept
{
    for (const auto& mesh : stroke_meshes_)
        stroke_renderer.draw_stroke_mesh(mesh);

    if (!brush.draw_finished())
        stroke_renderer.draw_stroke(brush.stroke());
}




void Canvas::add_stroke(const Stroke& stroke) noexcept
{
    if (stroke.points.empty())
        return;

    stroke_meshes_.push_back(stroke_mesh_generator.generate_mesh(stroke));
}