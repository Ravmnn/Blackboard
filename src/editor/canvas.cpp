#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>




using bb::editor::Canvas,
    bb::rendering::WindowRenderer,
    bb::rendering::TextureRenderer;




Canvas::Canvas(const StrokeMeshRenderer& mesh_renderer) noexcept : TextureRenderer(true),
    camera(*this, 0.2, 5, 0.13),

    stroke_mesh_generator(6),
    stroke_renderer(mesh_renderer, &stroke_mesh_generator, &camera)
{
    stroke_renderer.should_debug_draw_points = false;
    stroke_renderer.should_debug_draw_edges = false;
    stroke_renderer.should_debug_draw_samples = false;
    stroke_renderer.should_debug_draw_caps = false;

    camera.bounds_expansion = { 100, 100 };


    clear_color = BLANK;
}




void Canvas::initialize() noexcept
{
    resize_texture_renderer();

    Initializable::initialize();
}





void Canvas::update() noexcept
{
    initialize_if_uninitialized();

    if (IsWindowResized())
        resize_texture_renderer();

    camera.update();
}


void Canvas::resize_texture_renderer() noexcept
{
    resize(WindowRenderer::screen_resolution());
}




void Canvas::add_stroke(const Stroke& stroke) noexcept
{
    if (stroke.points.empty())
        return;

    auto mesh = stroke_mesh_generator.generate_mesh(stroke);

    if (mesh && !mesh->empty())
        stroke_meshes.push_back(std::move(mesh));
}