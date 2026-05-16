#include <blackboard/editor/editor.hpp>




Editor::Editor() noexcept :
    color_menu_(nullptr, { 600, 600 }, 100)
{
    window_renderer_.use_buffer_texture = false;


    left_button_.press.subscribe([this]() noexcept { canvas.current_tool->enable(); });
    left_button_.release.subscribe([this]() noexcept { canvas.current_tool->disable(); });

    aux_button_.press.subscribe([this]() noexcept { canvas.brush.color = canvas.background_color; canvas.current_tool->enable(); });
    aux_button_.release.subscribe([this]() noexcept { canvas.brush.color = canvas.DefaultBrushColor; canvas.current_tool->disable(); });


    new ColorMenuButton(&color_menu_, { 255, 60, 60, 255 });
    new ColorMenuButton(&color_menu_, { 60, 255, 60, 255 });
    new ColorMenuButton(&color_menu_, { 60, 60, 255, 255 });
    new ColorMenuButton(&color_menu_, { 255, 60, 255, 255 });
    new ColorMenuButton(&color_menu_, { 255, 255, 60, 255 });
    new ColorMenuButton(&color_menu_, { 60, 255, 255, 255 });
    new ColorMenuButton(&color_menu_, { 255, 255, 255, 255 });
    new ColorMenuButton(&color_menu_, { 0, 0, 0, 255 });
}




void Editor::update() noexcept
{
    update_mouse_buttons();
    update_keybindings();

    canvas.update();

    //button_->set_absolute_position(GetMousePosition() - button_->size() / 2);
    color_menu_.update();
}


void Editor::update_mouse_buttons() noexcept
{
    left_button_.update();
    aux_button_.update();
}


void Editor::update_keybindings() noexcept
{
    if (IsKeyPressed(KEY_ONE)) draw_statistics_ = !draw_statistics_;

    if (IsKeyPressed(KEY_TWO)) canvas.stroke_renderer.should_debug_draw_points = !canvas.stroke_renderer.should_debug_draw_points;
    if (IsKeyPressed(KEY_THREE)) canvas.stroke_renderer.should_debug_draw_samples = !canvas.stroke_renderer.should_debug_draw_samples;
    if (IsKeyPressed(KEY_FOUR)) canvas.stroke_renderer.should_debug_draw_edges = !canvas.stroke_renderer.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) canvas.stroke_renderer.should_debug_draw_caps = !canvas.stroke_renderer.should_debug_draw_caps;
}




void Editor::draw() noexcept
{
    window_renderer_.begin_render();
        canvas.draw();
        color_menu_.draw();

        draw_statistics();
    window_renderer_.end_render();
}


void Editor::draw_statistics() noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}