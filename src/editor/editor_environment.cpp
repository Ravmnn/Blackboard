#include <blackboard/editor/editor_environment.hpp>

#include <cassert>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorEnvironment;




EditorEnvironment::EditorEnvironment(Editor& editor) noexcept :
    editor(editor),

    left_button(MouseButtonEvent(MOUSE_BUTTON_LEFT, editor.canvas())),
    right_button(MouseButtonEvent(MOUSE_BUTTON_RIGHT, editor.canvas())),
    middle_button(MouseButtonEvent(MOUSE_BUTTON_MIDDLE, editor.canvas()))
{
    left_button.clickable = &editor;
    right_button.clickable = &editor;
    middle_button.clickable = &editor;

    left_button.press.subscribe([this](auto&) { on_left_button_press(); }, "editor::Environment::left_button_press_callback");
    left_button.release.subscribe([this](auto&) { on_left_button_release(); }, "editor::Environment::left_button_release_callback");
    left_button.click.subscribe([this](auto&) { on_left_button_click(); }, "editor::Environment::left_button_click_callback");
    left_button.drag_start.subscribe([this](auto&) { on_left_button_drag_start(); }, "editor::Environment::left_button_drag_start_callback");
    left_button.drag_end.subscribe([this](auto&) { on_left_button_drag_end(); }, "editor::Environment::left_button_drag_end_callback");

    left_button.late_press.subscribe([this](auto&) { on_left_button_late_press(); }, "editor::Environment::left_button_late_press_callback");
    left_button.late_release.subscribe([this](auto&) { on_left_button_late_release(); }, "editor::Environment::left_button_late_release_callback");
    left_button.late_click.subscribe([this](auto&) { on_left_button_late_click(); }, "editor::Environment::left_button_late_click_callback");
    left_button.late_drag_start.subscribe([this](auto&) { on_left_button_late_drag_start(); }, "editor::Environment::left_button_late_drag_start_callback");
    left_button.late_drag_end.subscribe([this](auto&) { on_left_button_late_drag_end(); }, "editor::Environment::left_button_late_drag_end_callback");

    right_button.press.subscribe([this](auto&) { on_right_button_press(); }, "editor::Environment::right_button_press_callback");
    right_button.release.subscribe([this](auto&) { on_right_button_release(); }, "editor::Environment::right_button_release_callback");
    right_button.click.subscribe([this](auto&) { on_right_button_click(); }, "editor::Environment::right_button_click_callback");
    right_button.drag_start.subscribe([this](auto&) { on_right_button_drag_start(); }, "editor::Environment::right_button_drag_start_callback");
    right_button.drag_end.subscribe([this](auto&) { on_right_button_drag_end(); }, "editor::Environment::right_button_drag_end_callback");

    right_button.late_press.subscribe([this](auto&) { on_right_button_late_press(); }, "editor::Environment::right_button_late_press_callback");
    right_button.late_release.subscribe([this](auto&) { on_right_button_late_release(); }, "editor::Environment::right_button_late_release_callback");
    right_button.late_click.subscribe([this](auto&) { on_right_button_late_click(); }, "editor::Environment::right_button_late_click_callback");
    right_button.late_drag_start.subscribe([this](auto&) { on_right_button_late_drag_start(); }, "editor::Environment::right_button_late_drag_start_callback");
    right_button.late_drag_end.subscribe([this](auto&) { on_right_button_late_drag_end(); }, "editor::Environment::right_button_late_drag_end_callback");

    middle_button.press.subscribe([this](auto&) { on_middle_button_press(); }, "editor::Environment::middle_button_press_callback");
    middle_button.release.subscribe([this](auto&) { on_middle_button_release(); }, "editor::Environment::middle_button_release_callback");
    middle_button.click.subscribe([this](auto&) { on_middle_button_click(); }, "editor::Environment::middle_button_click_callback");
    middle_button.drag_start.subscribe([this](auto&) { on_middle_button_drag_start(); }, "editor::Environment::middle_button_drag_start_callback");
    middle_button.drag_end.subscribe([this](auto&) { on_middle_button_drag_end(); }, "editor::Environment::middle_button_drag_end_callback");

    middle_button.late_press.subscribe([this](auto&) { on_middle_button_late_press(); }, "editor::Environment::middle_button_late_press_callback");
    middle_button.late_release.subscribe([this](auto&) { on_middle_button_late_release(); }, "editor::Environment::middle_button_late_release_callback");
    middle_button.late_click.subscribe([this](auto&) { on_middle_button_late_click(); }, "editor::Environment::middle_button_late_click_callback");
    middle_button.late_drag_start.subscribe([this](auto&) { on_middle_button_late_drag_start(); }, "editor::Environment::middle_button_late_drag_start_callback");
    middle_button.late_drag_end.subscribe([this](auto&) { on_middle_button_late_drag_end(); }, "editor::Environment::middle_button_late_drag_end_callback");
}




void EditorEnvironment::update() noexcept
{
    assert(current_tool_);

    for (auto& tool : tools_)
        tool->update();
}




void EditorEnvironment::draw() noexcept
{
    current_tool_->draw();
}




void EditorEnvironment::set_current_tool(Tool& tool) noexcept
{
    if (current_tool_ == &tool)
        return;

    if (current_tool_)
        current_tool_->changed_out.trigger();

    current_tool_ = &tool;
    current_tool_->changed_in.trigger();
}




void EditorEnvironment::on_enabled() noexcept
{
    current_tool()->changed_in.trigger();


    editor.add_mouse_button_event_or_assign(left_button);
    editor.add_mouse_button_event_or_assign(right_button);
    editor.add_mouse_button_event_or_assign(middle_button);

    editor.reset_buttons_state();
}


void EditorEnvironment::on_disabled() noexcept
{
    current_tool()->changed_out.trigger();
}