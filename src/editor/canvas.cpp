#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




Canvas::Canvas() :
    stroke_mesh_generator(6),
    stroke_renderer(stroke_mesh_generator, &canvas_camera),
    canvas_camera(*this, 0.2, 25, 0.13),

    brush(*this, DefaultBrushColor, 14),
    eraser(*this)
{
    stroke_renderer.should_debug_draw_points = false;
    stroke_renderer.should_debug_draw_edges = false;
    stroke_renderer.should_debug_draw_samples = false;
    stroke_renderer.should_debug_draw_caps = false;

    canvas_camera.bounds_expansion = { 100, 100 };

    current_tool = &brush;
}




void Canvas::update() noexcept
{
    if (!initialized_)
        initialize();

    if (IsWindowResized())
        recreate_texture_renderer();

    canvas_camera.update();
    current_tool->update();
}


void Canvas::initialize() noexcept
{
    recreate_texture_renderer();

    initialized_ = true;
}


void Canvas::recreate_texture_renderer() noexcept
{
    const Vector2 screen_resolution = WindowRenderer::screen_resolution();

    super_sampled_texture_ = TextureRenderer(screen_resolution * SuperSamplingFactor);
    super_sampled_texture_.clear_color = background_color;

    final_texture_ = TextureRenderer(screen_resolution);
}



void Canvas::draw() noexcept
{
    draw_to_super_sampled_texture();
    draw_super_sampled_to_final_texture();

    DrawTextureV(final_texture_.contents().texture, {}, WHITE);
}


void Canvas::draw_to_super_sampled_texture() noexcept
{
    super_sampled_texture_.begin_render();
    canvas_camera.enable();
        draw_strokes();
        current_tool->draw();
    canvas_camera.disable();
    super_sampled_texture_.end_render();

    super_sampled_texture_.generate_mipmaps();
}


void Canvas::draw_super_sampled_to_final_texture() noexcept
{
    const Texture contents = super_sampled_texture_.contents().texture;
    SetTextureFilter(contents, TEXTURE_FILTER_TRILINEAR);

    const Vector2 source_size = { (float)contents.width, (float)contents.height };
    const Vector2 target_size = final_texture_.resolution();
    const Rectangle source = { 0, 0, source_size.x, source_size.y };
    const Rectangle destination = { 0, 0, target_size.x, target_size.y };

    final_texture_.begin_render();
    DrawTexturePro(contents, source, destination, {}, 0, WHITE);
    final_texture_.end_render();
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