#include <blackboard/editor/editor.hpp>




Editor::Editor() noexcept
{
    window_renderer_.use_buffer_texture = false;


    color_menu_ = new ColorMenu;

    ui_context_.add_component(*color_menu_);


    left_button_.press.subscribe([this]() noexcept { canvas.current_tool->enable(); });
    left_button_.release.subscribe([this]() noexcept { canvas.current_tool->disable(); });

    aux_button_.press.subscribe([this]() noexcept { canvas.brush.color = canvas.background_color; canvas.current_tool->enable(); });
    aux_button_.release.subscribe([this]() noexcept { canvas.brush.color = canvas.DefaultBrushColor; canvas.current_tool->disable(); });

    middle_button_.click.subscribe([this]() noexcept { color_menu_->toggle(GetMousePosition()); });


    new ColorMenuButton(color_menu_, canvas.DefaultBrushColor);
    new ColorMenuButton(color_menu_, { 255, 255, 255, 255 });
    new ColorMenuButton(color_menu_, { 0, 0, 0, 255 });
    new ColorMenuButton(color_menu_, { 50, 50, 50, 255 });
    new ColorMenuButton(color_menu_, { 128, 128, 128, 255 });
    new ColorMenuButton(color_menu_, { 200, 200, 200, 255 });
    new ColorMenuButton(color_menu_, { 220, 38, 38, 255 });
    new ColorMenuButton(color_menu_, { 153, 27, 27, 255 });
    new ColorMenuButton(color_menu_, { 248, 113, 113, 255 });
    new ColorMenuButton(color_menu_, { 236, 72, 153, 255 });
    new ColorMenuButton(color_menu_, { 251, 182, 206, 255 });
    new ColorMenuButton(color_menu_, { 217, 70, 239, 255 });
    new ColorMenuButton(color_menu_, { 124, 58, 237, 255 });
    new ColorMenuButton(color_menu_, { 76, 29, 149, 255 });
    new ColorMenuButton(color_menu_, { 67, 56, 202, 255 });
    new ColorMenuButton(color_menu_, { 37, 99, 235, 255 });
    new ColorMenuButton(color_menu_, { 59, 130, 246, 255 });
    new ColorMenuButton(color_menu_, { 14, 165, 233, 255 });
    new ColorMenuButton(color_menu_, { 6, 182, 212, 255 });
    new ColorMenuButton(color_menu_, { 20, 184, 166, 255 });
    new ColorMenuButton(color_menu_, { 22, 163, 74, 255 });
    new ColorMenuButton(color_menu_, { 74, 222, 128, 255 });
    new ColorMenuButton(color_menu_, { 132, 204, 22, 255 });
    new ColorMenuButton(color_menu_, { 163, 230, 53, 255 });
    new ColorMenuButton(color_menu_, { 234, 179, 8, 255 });
    new ColorMenuButton(color_menu_, { 253, 224, 71, 255 });
    new ColorMenuButton(color_menu_, { 234, 88, 12, 255 });
    new ColorMenuButton(color_menu_, { 251, 146, 60, 255 });
    new ColorMenuButton(color_menu_, { 120, 53, 15, 255 });
    new ColorMenuButton(color_menu_, { 161, 98, 7, 255 });
    new ColorMenuButton(color_menu_, { 214, 188, 150, 255 });


    color_menu_->color_selected.subscribe([this](const Color& color) { canvas.brush.color = color; });
}




void Editor::update() noexcept
{
    update_mouse_buttons();
    update_keybindings();

    canvas.update();

    ui_context_.update();
}


void Editor::update_mouse_buttons() noexcept
{
    left_button_.update();
    aux_button_.update();
    middle_button_.update();
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
        ui_context_.draw();

        draw_statistics();
    window_renderer_.end_render();
}


void Editor::draw_statistics() noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}