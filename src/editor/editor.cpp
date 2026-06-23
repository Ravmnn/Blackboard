#include <blackboard/editor/editor.hpp>




using bb::editor::Editor,
    bb::ui::Component,
    bb::ui::Context;




Editor::Editor(Context& context) noexcept :
    Component(nullptr, {}), Clickable(&canvas),

    canvas(Palette(DefaultPaletteColor)),

    brush(canvas, 14),
    eraser(canvas)
{
    clip = false;


    current_tool = &brush;


    this->context = &context;
    this->context->add_component(*this);

    color_menu_ = new ColorMenu(this);
    color_menu_->clip = false;


    left_button_.press.subscribe([this]() noexcept { current_tool->enable(); });
    left_button_.release.subscribe([this]() noexcept { current_tool->disable(); });

    right_button_.min_drag_distance = 150;
    right_button_.click.subscribe([this]() noexcept { alternate_tool(); });
    right_button_.drag_start.subscribe([this]() noexcept { alternate_tool(); current_tool->enable(); });
    right_button_.drag_end.subscribe([this]() noexcept { current_tool->disable(); alternate_tool(); });

    middle_button_.click.subscribe([this]() noexcept { color_menu_->toggle(GetMousePosition()); });


    add_mouse_button_event(left_button_);
    add_mouse_button_event(right_button_);
    add_mouse_button_event(middle_button_);


    new ColorMenuButton(color_menu_, DefaultPaletteColor);
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
    color_menu_->hide();


    color_menu_->color_selected.subscribe([this](const Color& color) { canvas.palette.set_current_color(color); });
}




void Editor::update() noexcept
{
    update_focus();
    update_keybindings();
    update_tools();

    canvas.update();
    draw_canvas();

    Clickable::update();
    Component::update();
}


void Editor::update_focus() noexcept
{
    if (is_pressed() && context->component_with_mouse_input() == this)
        context->set_focus_to(this);
}


void Editor::update_tools() noexcept
{
    brush.update();
    eraser.update();
}


void Editor::update_keybindings() noexcept
{
    if (IsKeyPressed(KEY_ONE)) draw_statistics_ = !draw_statistics_;

    if (IsKeyPressed(KEY_TWO)) canvas.stroke_renderer.should_debug_draw_points = !canvas.stroke_renderer.should_debug_draw_points;
    if (IsKeyPressed(KEY_THREE)) canvas.stroke_renderer.should_debug_draw_samples = !canvas.stroke_renderer.should_debug_draw_samples;
    if (IsKeyPressed(KEY_FOUR)) canvas.stroke_renderer.should_debug_draw_edges = !canvas.stroke_renderer.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) canvas.stroke_renderer.should_debug_draw_caps = !canvas.stroke_renderer.should_debug_draw_caps;
}




void Editor::draw_self() noexcept
{
    draw_canvas_content();
    draw_statistics();
}


void Editor::draw_canvas() noexcept
{
    canvas.canvas_renderer.begin_render();
    canvas.camera.enable();
        canvas.draw_strokes();

        if (!brush.draw_finished())
            canvas.stroke_renderer.draw_stroke(brush.stroke());

        current_tool->draw();
    canvas.camera.disable();
    canvas.canvas_renderer.end_render();
}


void Editor::draw_canvas_content() noexcept
{
    canvas.canvas_renderer.draw_contents_texture();
}


void Editor::draw_statistics() const noexcept
{
    if (!draw_statistics_)
        return;

    DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 30, WHITE);
}