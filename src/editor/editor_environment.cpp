#include <blackboard/editor/editor_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorEnvironment;




EditorEnvironment::EditorEnvironment(Editor& editor) noexcept :
    editor(editor),

    left_button(MouseButtonEvent(MOUSE_BUTTON_LEFT, editor.canvas)),
    right_button(MouseButtonEvent(MOUSE_BUTTON_RIGHT, editor.canvas)),
    middle_button(MouseButtonEvent(MOUSE_BUTTON_MIDDLE, editor.canvas))
{
    middle_button.enable_late_mode = true;
}




void EditorEnvironment::update() noexcept
{
    for (auto& tool : tools_)
        tool->update();
}




void EditorEnvironment::enable() noexcept
{
    editor.add_mouse_button_event_or_assign(left_button);
    editor.add_mouse_button_event_or_assign(right_button);
    editor.add_mouse_button_event_or_assign(middle_button);

    Activatable::enable();
}