#include <blackboard/editor/editor_drawing_environment.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/ui/color_menu.hpp>




using bb::editor::EditorDrawingEnvironment;




// TODO: LMB selecting replaces selection. RMB selecting appends selection
EditorDrawingEnvironment::EditorDrawingEnvironment(Editor& editor) noexcept : EditorEnvironment(editor),
    brush(*this, 14),
    eraser(*this)
{
    tools_.push_back(&brush);
    tools_.push_back(&eraser);

    set_current_tool(brush);


    right_button.min_drag_distance = 75;
    right_button.time_to_enter_late_mode = std::chrono::milliseconds(150);
    right_button.enable_late_mode = true;
    right_button.exclusive_late_mode = true;
}




void EditorDrawingEnvironment::alternate_brush_and_eraser() noexcept
{
    set_current_tool(current_tool() == &brush ? (Tool&)eraser : (Tool&)brush);
}




void EditorDrawingEnvironment::enter_selection_mode(const bool enable_selection) noexcept
{
    editor.set_current_environment(editor.selection_environment);

    if (!enable_selection)
        return;

    editor.selection_environment.set_current_tool(editor.selection_environment.selection);
    editor.selection_environment.current_tool()->enable();
}




void EditorDrawingEnvironment::on_enabled() noexcept
{
    EditorEnvironment::on_enabled();

    editor.dynamic_background_color = true;
}




void EditorDrawingEnvironment::on_left_button_press() noexcept
{
    current_tool_->enable();
}


void EditorDrawingEnvironment::on_left_button_release() noexcept
{
    current_tool_->disable();
}




void EditorDrawingEnvironment::on_right_button_click() noexcept
{
    editor.get_stroke_under_mouse() ? enter_selection_mode(false) : alternate_brush_and_eraser();
}


void EditorDrawingEnvironment::on_right_button_late_click() noexcept
{
    const StrokeMesh* const stroke = editor.get_stroke_under_mouse();

    if (stroke)
        editor.palette.set_current_color(stroke->front().color);
}


void EditorDrawingEnvironment::on_right_button_drag_start() noexcept
{
    enter_selection_mode();
}




void EditorDrawingEnvironment::on_middle_button_click() noexcept
{
    editor.color_menu->toggle(GetMousePosition());
}
