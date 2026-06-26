#include <blackboard/editor/editor_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorEnvironment;




EditorEnvironment::EditorEnvironment(Editor& editor) noexcept :
    left_button_(MouseButtonEvent(MOUSE_BUTTON_LEFT, editor.canvas)),
    right_button_(MouseButtonEvent(MOUSE_BUTTON_RIGHT, editor.canvas)),
    middle_button_(MouseButtonEvent(MOUSE_BUTTON_MIDDLE, editor.canvas)),

    editor(editor)
{
    editor.add_mouse_button_event(left_button_);
    editor.add_mouse_button_event(right_button_);
    editor.add_mouse_button_event(middle_button_);
}




void EditorEnvironment::update() noexcept
{
    for (auto& tool : tools_)
        tool->update();
}