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

    left_button_.press.subscribe([&]() noexcept { editor.current_tool->enable(); });
    left_button_.release.subscribe([&]() noexcept { editor.current_tool->disable(); });

    right_button_.min_drag_distance = 75;
    right_button_.click.subscribe([&]() noexcept { alternate_brush_and_eraser(); });
    right_button_.drag_start.subscribe([&]() noexcept { alternate_brush_and_eraser(); editor.current_tool->enable(); });
    right_button_.drag_end.subscribe([&]() noexcept { editor.current_tool->disable(); alternate_brush_and_eraser(); });

    middle_button_.click.subscribe([&]() noexcept { editor.color_menu->toggle(GetMousePosition()); });
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