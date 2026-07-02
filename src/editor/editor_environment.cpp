#include <blackboard/editor/editor_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorEnvironment;




EditorEnvironment::EditorEnvironment(Editor& editor) noexcept :
    editor(editor),

    left_button(MouseButtonEvent(MOUSE_BUTTON_LEFT, editor.canvas)),
    right_button(MouseButtonEvent(MOUSE_BUTTON_RIGHT, editor.canvas)),
    middle_button(MouseButtonEvent(MOUSE_BUTTON_MIDDLE, editor.canvas))
{
    left_button.clickable = &editor;
    right_button.clickable = &editor;
    middle_button.clickable = &editor;
}




void EditorEnvironment::update() noexcept
{
    assert(current_tool);

    for (auto& tool : tools_)
        tool->update();
}




void EditorEnvironment::draw() noexcept
{
    current_tool->draw();
}




void EditorEnvironment::on_enabled() noexcept
{
    editor.add_mouse_button_event_or_assign(left_button);
    editor.add_mouse_button_event_or_assign(right_button);
    editor.add_mouse_button_event_or_assign(middle_button);

    editor.reset_buttons_state();
}