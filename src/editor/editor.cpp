#include <blackboard/editor/editor.hpp>




Editor::Editor() noexcept :
    parent_rectangle_(nullptr, Vector2{100, 100}, Vector2{ 800, 600 }, 25, WHITE)
{
    window_renderer_.use_buffer_texture = false;


    left_button_.on_press.subscribe([this]() noexcept { canvas.current_tool->enable(); });
    left_button_.on_release.subscribe([this]() noexcept { canvas.current_tool->disable(); });

    aux_button_.on_press.subscribe([this]() noexcept { canvas.brush.color = canvas.background_color; canvas.current_tool->enable(); });
    aux_button_.on_release.subscribe([this]() noexcept { canvas.brush.color = canvas.DefaultBrushColor; canvas.current_tool->disable(); });


    rectangle_ = new RoundedRectangle(&parent_rectangle_, Vector2{}, Vector2{ 100, 100 }, 10, Color{ 255, 180, 180, 255 });

    rectangle_->outline_thickness = 2;
    rectangle_->outline_color = Color{ 255, 100, 100, 255 };
    parent_rectangle_.outline_thickness = 2;
    parent_rectangle_.outline_color = Color{ 255, 100, 255, 255 };
}




void Editor::update() noexcept
{
    update_mouse_buttons();
    update_keybindings();

    canvas.update();

    rectangle_->set_absolute_position(GetMousePosition() - rectangle_->size() / 2);
    parent_rectangle_.update();
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
        parent_rectangle_.draw();

        draw_statistics();
    window_renderer_.end_render();
}


void Editor::draw_statistics() noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}