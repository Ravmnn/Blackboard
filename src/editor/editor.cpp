#include <blackboard/editor/editor.hpp>

#include <rlgl.h>

#include <blackboard/camera_matrix.hpp>
#include <blackboard/debug/gl_to_string.hpp>
#include <blackboard/debug/profiler.hpp>
#include <blackboard/debug/logger.hpp>
#include <blackboard/ui/context.hpp>
#include <blackboard/editor/ui/color_menu.hpp>
#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>
#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>




using
bb::math::Segment,
bb::debug::GlToString,
bb::debug::Profiler,
bb::debug::Logger,
bb::rendering::TextureRenderer,
bb::ui::Context,
bb::ui::Component,
bb::editor::StrokeMesh,
bb::editor::StrokeMeshCollider,
bb::editor::Editor;




Editor::Editor(Context& ui_context) noexcept :
    Component(nullptr, {}),
    Clickable(*dynamic_cast<MousePositionProvider*>(new Canvas(this))),

    // workaround to initialization order
    canvas_(const_cast<Canvas*>(dynamic_cast<const Canvas*>(&mouse_position_provider))),
    background_(*this, 2, 0.5),

    mouse_late_mode_indicator_(*canvas_, *this),

    parent_rect_(this, {600, 600}, { 800, 600 }, 20, RED, 3, BLUE),
    child_rect_(&parent_rect_, {}, { 200, 200 }, 5, MAGENTA, 3, GREEN),

    stroke_mesh_generator(6),

    draw_environment(*this),
    selection_environment(*this),

    palette(DefaultPaletteColor)
{
    clip = false;
    parent_rect_.clip = false;
    child_rect_.clip = false;

    stroke_renderer.effect.smoothness = 0.2;
    stroke_renderer.effect.smoothness_thickness_influence = 25;


    set_current_environment(draw_environment);

    environment_changed.subscribe([this]() noexcept { on_environment_changed(); }, "editor::Editor::environment_changed_callback");
    tool_changed.subscribe([this]() noexcept { on_tool_changed(); }, "editor::Editor::tool_changed_callback");


    this->ui_context = &ui_context;
    this->ui_context->add_component(*this);

    color_menu = new ColorMenu(this);
    color_menu->add_colors({
        DefaultPaletteColor,
        { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, { 50, 50, 50, 255 },
        { 128, 128, 128, 255 }, { 200, 200, 200, 255 }, { 220, 38, 38, 255 },
        { 153, 27, 27, 255 }, { 248, 113, 113, 255 }, { 236, 72, 153, 255 },
        { 251, 182, 206, 255 }, { 217, 70, 239, 255 }, { 124, 58, 237, 255 },
        { 76, 29, 149, 255 }, { 67, 56, 202, 255 }, { 37, 99, 235, 255 },
        { 59, 130, 246, 255 }, { 14, 165, 233, 255 }, { 6, 182, 212, 255 },
        { 20, 184, 166, 255 }, { 22, 163, 74, 255 }, { 74, 222, 128, 255 },
        { 132, 204, 22, 255 }, { 163, 230, 53, 255 }, { 234, 179, 8, 255 },
        { 253, 224, 71, 255 }, { 234, 88, 12, 255 }, { 251, 146, 60, 255 },
        { 120, 53, 15, 255 }, { 161, 98, 7, 255 }, { 214, 188, 150, 255 }
    });
    color_menu->hide();

    color_menu->color_selected.subscribe([this](const Color& color) { palette.set_current_color(color); });


    log_canvas_framebuffer_status();
}


void Editor::log_canvas_framebuffer_status() noexcept
{
    const int status = canvas_->frame_buffer().gl_status();
    const std::string status_string = GlToString::frame_buffer_status(status);
    const std::string message = std::format("Canvas framebuffer status: {0} ({1:x} = {1})", status_string, status);

    Logger::info(message);
}




void Editor::update() noexcept
{
    Profiler::begin("editor::update");


    // update_focus();
    // update_background();

    Clickable::update();
    Component::update();

    // background_.update();
    // current_environment_->update();
    // mouse_late_mode_indicator_.update();

    // update_tool_changed_event();
    // update_vanish_animations();
    // update_effects();
    // update_keybindings();

    // stroke_renderer.view_area = canvas_->camera.bounding_box();
    // stroke_renderer.update();


    Profiler::end();
}


void Editor::update_focus() noexcept
{
    if (is_pressed() && caught_mouse_input)
        ui_context->set_focus_to(this);

    canvas_->camera.disable_move = canvas_->camera.disable_zoom = !caught_mouse_input;
}


void Editor::update_background() noexcept
{
    if (dynamic_background_color)
        background_.effect.background_color = palette.background_color_from_current();
    else
        background_.effect.background_color = DefaultBackgroundColor;
}


void Editor::update_tool_changed_event() noexcept
{
    if (current_environment_->current_tool() != last_tool_)
        tool_changed.trigger();

    last_tool_ = current_environment_->current_tool();
}


void Editor::update_vanish_animations() noexcept
{
    std::erase_if(vanish_animations_, [](const auto& vanish) noexcept { return vanish->is_transparent(); });

    for (auto& vanish : vanish_animations_)
        if (vanish)
            vanish->update();
}


void Editor::update_effects() noexcept
{
    stroke_renderer.effect.mvp = CameraMatrix::get_orthographic_matrix_from_camera(canvas_->raylib_camera()   );
    stroke_renderer.effect.camera_zoom = canvas_->raylib_camera().zoom;

    stroke_renderer.effect.update();
}


void Editor::update_keybindings() noexcept
{
    if (!caught_mouse_input)
        return;

    if (IsKeyPressed(KEY_ONE)) stroke_debug_renderer.draw_points = !stroke_debug_renderer.draw_points;
    if (IsKeyPressed(KEY_TWO)) stroke_debug_renderer.draw_samples = !stroke_debug_renderer.draw_samples;
    if (IsKeyPressed(KEY_THREE)) stroke_debug_renderer.draw_edges = !stroke_debug_renderer.draw_edges;
    if (IsKeyPressed(KEY_FOUR)) wire_mode = !wire_mode;
}








void Editor::draw_self() noexcept
{
    Profiler::begin("editor::draw");


    // draw_background();
    // draw_strokes();

    // draw_to_canvas();


    Profiler::end();
}


void Editor::draw_to_canvas() noexcept
{
    Profiler::begin("editor::draw::canvas");


    canvas_->begin_render();
        stroke_renderer.draw_composition();

        canvas_->camera.enable();
            draw_debug_strokes();

            current_environment_->draw();
            mouse_late_mode_indicator_.draw();

            draw_vanish_animations();
        canvas_->camera.disable();
    canvas_->end_render();


    Profiler::end();
}


void Editor::draw_background() noexcept
{
    canvas_->camera.enable();
    background_.draw();
    canvas_->camera.disable();
}


void Editor::draw_strokes() noexcept
{
    Profiler::begin("editor::draw::strokes");


    if (wire_mode)
        rlEnableWireMode();

    stroke_renderer.clear_composition();
    draw_cached_and_brush_strokes();

    rlDisableWireMode();


    Profiler::end();
}


void Editor::draw_cached_and_brush_strokes() noexcept
{
    for (auto& mesh : meshes)
        stroke_renderer.draw_stroke_mesh_gl(*mesh);

    if (!draw_environment.brush.draw_finished())
        if (auto brush_stroke = brush_stroke_mesh())
            stroke_renderer.draw_stroke_mesh(*brush_stroke);
}


void Editor::draw_debug_strokes() noexcept
{
    if (!stroke_debug_renderer.any_draw_enabled())
        return;

    for (const auto& mesh : meshes)
        stroke_debug_renderer.draw(*mesh->source);

    const auto brush_mesh = stroke_mesh_generator.generate_mesh(draw_environment.brush.stroke());

    if (brush_mesh)
        stroke_debug_renderer.draw(*brush_mesh);
}


void Editor::draw_vanish_animations() noexcept
{
    for (auto& vanish : vanish_animations_)
        if (vanish)
            vanish->draw();
}




void Editor::set_current_environment(EditorEnvironment& environment) noexcept
{
    if (current_environment_)
        current_environment_->disable();

    current_environment_ = &environment;
    current_environment_->enable();

    environment_changed.trigger();
}




StrokeMesh* Editor::get_stroke_under_point(const Vector2& point) noexcept
{
    for (auto& stroke : meshes)
        if (StrokeMeshCollider::stroke_contains_point(*stroke->source, point))
            return stroke->source.get();

    return nullptr;
}


StrokeMesh* Editor::get_stroke_intersecting_segment(const Segment& segment) noexcept
{
    for (auto& stroke : meshes)
        if (StrokeMeshCollider::stroke_intersects_with_segment(*stroke->source, segment))
            return stroke->source.get();

    return nullptr;
}




void Editor::add_stroke(const Stroke& stroke) noexcept
{
    std::unique_ptr<StrokeMesh> mesh = stroke_mesh_generator.generate_mesh(stroke);

    if (!mesh)
        return;

    std::unique_ptr<StrokeMeshGL> mesh_gl = StrokeMeshGLBuilder().build(mesh);
    meshes.push_back(std::move(mesh_gl));
}


void Editor::remove_stroke(const StrokeMesh& mesh) noexcept
{
    std::erase_if(meshes, [&](const std::unique_ptr<StrokeMeshGL>& stroke_mesh_gl) {
        return stroke_mesh_gl->source.get() == &mesh;
    });
}








void Editor::on_environment_changed() noexcept
{

}


void Editor::on_tool_changed() noexcept
{
    if (!last_tool_)
        return;

    constexpr float ScaleSpeed = 2.5;
    constexpr float TransparencySpeed = 1.75;

    auto vanish = std::make_unique<Vanish<Tool>>(*last_tool_, ScaleSpeed, TransparencySpeed);
    vanish_animations_.push_back(std::move(vanish));
}