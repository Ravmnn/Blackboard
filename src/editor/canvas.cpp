#include <blackboard/editor/canvas.hpp>

#include <flustral/rendering/effects/effect_pass.hpp>

#include <blackboard/tween.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




Canvas::Canvas()
    : stroke_renderer_(16), canvas_camera_(*this, 0.2, 15, 0.13),
        brush(*this, Color(211, 211, 211, 255), 14)
{
    stroke_renderer_.should_debug_draw_points = false;
    stroke_renderer_.should_debug_draw_edges = false;
    stroke_renderer_.should_debug_draw_samples = false;

    window_renderer_.use_buffer_texture = false;
}




void Canvas::update() noexcept
{
    if (!initialized_)
        initialize();

    if (IsWindowResized())
        recreate_texture_renderer();

    canvas_camera_.update();

    update_drawing();
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



void Canvas::update_drawing() noexcept
{
    brush.update();

    if (brush.draw_finished())
        drawn_strokes.push_back(brush.stroke());

    if (!IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        return;

    drawn_strokes.clear();
    brush.clear_stroke();
}




void Canvas::draw() noexcept
{
    texture_renderer_.begin_render();
    draw_strokes();
    texture_renderer_.end_render();

    texture_renderer_.generate_mipmaps();

    window_renderer_.begin_render();
    draw_antialiased_contents();
    window_renderer_.end_render();
}


void Canvas::draw_strokes() noexcept
{
    canvas_camera_.enable();

    stroke_renderer_.draw_stroke(brush.stroke());

    for (auto& stroke : drawn_strokes)
        stroke_renderer_.draw_stroke(stroke);

    canvas_camera_.disable();
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