#include <blackboard/editor/canvas.hpp>

#include <blackboard/timer.hpp>
#include <blackboard/rendering/effects/effect_pass.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




Canvas::Canvas() :
    stroke_mesh_generator_(6),
    stroke_renderer_(stroke_mesh_generator_, &canvas_camera_),
    canvas_camera_(*this, 0.2, 25, 0.13),

    brush(*this, DefaultBrushColor, 14),
    eraser(*this)
{
    stroke_renderer_.should_debug_draw_points = false;
    stroke_renderer_.should_debug_draw_edges = false;
    stroke_renderer_.should_debug_draw_samples = false;
    stroke_renderer_.should_debug_draw_caps = false;

    canvas_camera_.bounds_expansion = { 100, 100 };

    window_renderer_.use_buffer_texture = false;

    current_tool = &brush;


    left_button_.on_press.subscribe([this]() noexcept { current_tool->enable(); });
    left_button_.on_release.subscribe([this]() noexcept { current_tool->disable(); });

    aux_button_.on_press.subscribe([this]() noexcept { brush.color = background_color(); current_tool->enable(); });
    aux_button_.on_release.subscribe([this]() noexcept { brush.color = DefaultBrushColor; current_tool->disable(); });
}




void Canvas::update() noexcept
{
    if (!initialized_)
        initialize();

    update_input();

    canvas_camera_.update();
    current_tool->update();
}


void Canvas::initialize() noexcept
{
    recreate_texture_renderer();

    initialized_ = true;
}


void Canvas::recreate_texture_renderer() noexcept
{
    texture_renderer_ = TextureRenderer(window_renderer_.resolution() * SuperSamplingFactor);
    texture_renderer_.clear_color = background_color_;
}


void Canvas::update_input() noexcept
{
    if (IsWindowResized())
        recreate_texture_renderer();

    if (IsKeyPressed(KEY_ONE)) draw_statistics_ = !draw_statistics_;

    if (IsKeyPressed(KEY_TWO)) stroke_renderer_.should_debug_draw_points = !stroke_renderer_.should_debug_draw_points;
    if (IsKeyPressed(KEY_THREE)) stroke_renderer_.should_debug_draw_samples = !stroke_renderer_.should_debug_draw_samples;
    if (IsKeyPressed(KEY_FOUR)) stroke_renderer_.should_debug_draw_edges = !stroke_renderer_.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) stroke_renderer_.should_debug_draw_caps = !stroke_renderer_.should_debug_draw_caps;

    update_mouse_buttons();
}


void Canvas::update_mouse_buttons() noexcept
{
    left_button_.update();
    aux_button_.update();
}




void Canvas::draw() noexcept
{
    draw_to_buffer_texture();
    draw_buffer_texture_to_window();
}


void Canvas::draw_to_buffer_texture() noexcept
{
    texture_renderer_.begin_render();
    canvas_camera_.enable();

    draw_strokes();
    current_tool->draw();
    texture_renderer_.end_render();

    canvas_camera_.disable();
    texture_renderer_.generate_mipmaps();
}


void Canvas::draw_buffer_texture_to_window() noexcept
{
    window_renderer_.begin_render();
    draw_antialiased_contents();
    draw_statistics();
    window_renderer_.end_render();
}


void Canvas::draw_strokes() noexcept
{
    for (const auto& mesh : stroke_meshes_)
        stroke_renderer_.draw_stroke_mesh(mesh);

    if (!brush.draw_finished())
        stroke_renderer_.draw_stroke(brush.stroke());
}


void Canvas::draw_antialiased_contents() noexcept
{
    const Texture contents = texture_renderer_.contents().texture;
    SetTextureFilter(contents, TEXTURE_FILTER_TRILINEAR);

    const Vector2 source_size = { contents.width, contents.height };
    const Vector2 target_size = window_renderer_.resolution();
    const Rectangle source = { 0, 0, source_size.x, -source_size.y };
    const Rectangle destination = { 0, 0, target_size.x, target_size.y };

    DrawTexturePro(contents, source, destination, {}, 0, WHITE);
}


void Canvas::draw_statistics() noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}




void Canvas::add_stroke(const Stroke& stroke) noexcept
{
    if (stroke.points.empty())
        return;

    stroke_meshes_.push_back(stroke_mesh_generator_.generate_mesh(stroke));
}