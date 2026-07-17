#include <blackboard/editor/editor.hpp>

#include <rlgl.h>

#include <blackboard/ui/context.hpp>
#include <blackboard/editor/ui/color_menu.hpp>
#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>
#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>




using bb::editor::Editor,
    bb::math::Segment,
    bb::ui::Component,
    bb::ui::Context,
    bb::editor::StrokeMesh,
    bb::editor::StrokeMeshCollider,
    bb::rendering::TextureRenderer;




Editor::Editor(Context& ui_context) noexcept :
    Component(nullptr, {}),
    Clickable(canvas),

    background(*this, 1, 0.35),

    palette(DefaultPaletteColor),

    draw_environment(*this),
    selection_environment(*this),

    mouse_late_mode_indicator(canvas, *this)
{
    clip = false;


    background.max_alpha_factor = 0.40;

    stroke_effect_.smoothness = 0.3;


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
}




void Editor::update() noexcept
{
    update_focus();
    update_keybindings();
    update_background();

    Clickable::update();


    background.update();
    current_environment->update();
    mouse_late_mode_indicator.update();

    update_tool_changed_event();
    update_vanish_animations();

    stroke_manager.renderer.view_area = canvas.camera.bounding_box();
    canvas.update();


    const Matrix view = GetCameraMatrix2D(canvas.raylib_camera());
    const Matrix ortho =  MatrixOrtho(0, GetScreenWidth(), GetScreenHeight(), 0, -1, 1);
    const Matrix mvp = MatrixMultiply(view, ortho);

    stroke_effect_.mvp = mvp;
    stroke_effect_.camera_zoom = canvas.raylib_camera().zoom;

    stroke_effect_.update();


    Component::update();
}


void Editor::update_focus() noexcept
{
    if (is_pressed() && ui_context->component_with_mouse_input() == this)
        ui_context->set_focus_to(this);
}


void Editor::update_keybindings() noexcept
{
    if (IsKeyPressed(KEY_ONE)) draw_statistics_ = !draw_statistics_;

    if (IsKeyPressed(KEY_TWO)) stroke_manager.renderer.should_debug_draw_points = !stroke_manager.renderer.should_debug_draw_points;
    if (IsKeyPressed(KEY_THREE)) stroke_manager.renderer.should_debug_draw_samples = !stroke_manager.renderer.should_debug_draw_samples;
    if (IsKeyPressed(KEY_FOUR)) stroke_manager.renderer.should_debug_draw_edges = !stroke_manager.renderer.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) wire_mode_ = !wire_mode_;
}


void Editor::update_background() noexcept
{
    if (dynamic_background_color)
        background.effect.background_color = palette.background_color_from_current();
    else
        background.effect.background_color = DefaultBackgroundColor;
}


void Editor::update_tool_changed_event() noexcept
{
    if (current_environment->current_tool() != last_tool_)
        tool_changed.trigger();

    last_tool_ = current_environment->current_tool();
}


void Editor::update_vanish_animations() noexcept
{
    std::erase_if(vanish_animations_, [](const auto& vanish) noexcept { return vanish->is_transparent(); });

    for (auto& vanish : vanish_animations_)
        if (vanish)
            vanish->update();
}




void Editor::draw_self() noexcept
{
    draw_to_canvas();
    draw_canvas_content();
    draw_statistics();
}


void Editor::draw_to_canvas() noexcept
{
    canvas.camera.enable();
    background.draw();
    canvas.camera.disable();

    // TODO: cleanup
    // TODO: make StrokeMeshRender to use the shader or just remove it
    // TODO: support caps

    canvas.begin_render();
    canvas.camera.enable();
        if (wire_mode_)
            rlEnableWireMode();

        for (const auto& mesh : stroke_manager.meshes)
        {
            StrokeMeshGL mesh_gl = StrokeMeshGL::from_stroke(*mesh);
            mesh_gl.load_gl_data();

            stroke_effect_.enable();
            mesh_gl.draw();
            stroke_effect_.disable();

            mesh_gl.unload_gl_data();
        }

        rlDisableWireMode();


        current_environment->draw();
        mouse_late_mode_indicator.draw();

        draw_vanish_animations();
    canvas.camera.disable();
    canvas.end_render();
}


void Editor::draw_vanish_animations() noexcept
{
    for (auto& vanish : vanish_animations_)
        if (vanish)
            vanish->draw();
}


void Editor::draw_canvas_content() noexcept
{
    TextureRenderer::draw_y_inverted_texture(canvas.contents().texture);
}


void Editor::draw_statistics() const noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}




void Editor::set_current_environment(EditorEnvironment& environment) noexcept
{
    if (current_environment)
        current_environment->disable();

    current_environment = &environment;
    current_environment->enable();

    environment_changed.trigger();
}




StrokeMesh* Editor::get_stroke_under_point(const Vector2& point) noexcept
{
    for (auto& stroke : stroke_manager.meshes)
        if (StrokeMeshCollider::stroke_contains_point(*stroke, point))
            return stroke.get();

    return nullptr;
}


StrokeMesh* Editor::get_stroke_intersecting_segment(const Segment& segment) noexcept
{
    for (auto& stroke : stroke_manager.meshes)
        if (StrokeMeshCollider::stroke_intersects_with_segment(*stroke, segment))
            return stroke.get();

    return nullptr;
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

    vanish_animations_.push_back(std::make_unique<Vanish<Tool>>(*last_tool_, ScaleSpeed, TransparencySpeed));
}