#include <blackboard/editor/editor_drawing_environment.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/ui/color_menu.hpp>




using bb::editor::EditorDrawingEnvironment;




EditorDrawingEnvironment::EditorDrawingEnvironment(Editor& editor) noexcept : EditorEnvironment(editor),
    brush(editor, 14),
    eraser(editor)
{
    tools_.push_back(&brush);
    tools_.push_back(&eraser);

    left_button.press.subscribe([&](const auto&) noexcept { editor.current_tool->enable(); });
    left_button.release.subscribe([&](const auto&) noexcept { editor.current_tool->disable(); });

    right_button.min_drag_distance = 75;
    right_button.click.subscribe([&](const auto&) noexcept { alternate_brush_and_eraser(); });
    right_button.drag_start.subscribe([&](const auto&) noexcept { alternate_brush_and_eraser(); editor.current_tool->enable(); });
    right_button.drag_end.subscribe([&](const auto&) noexcept { editor.current_tool->disable(); alternate_brush_and_eraser(); });

    middle_button.click.subscribe([&](const auto&) noexcept { editor.color_menu->toggle(GetMousePosition()); });


    right_button.enable_late_mode = true;
    right_button.exclusive_late_mode = true;
}




void EditorDrawingEnvironment::draw() noexcept
{
    if (!brush.draw_finished())
        editor.canvas.stroke_renderer.draw_stroke(brush.stroke());
}




void EditorDrawingEnvironment::alternate_brush_and_eraser() noexcept
{
    editor.current_tool = editor.current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush;
}