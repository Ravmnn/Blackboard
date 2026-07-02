#include <blackboard/editor/editor_selection_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorSelectionEnvironment;




EditorSelectionEnvironment::EditorSelectionEnvironment(Editor& editor) noexcept : EditorEnvironment(editor),
    selection(editor)
{
    tools_.push_back(&selection);

    current_tool = &selection;


    negative_effect_.default_color = RED;


    left_button.press.subscribe([this](const auto&) noexcept { current_tool->enable(); });
    left_button.release.subscribe([this](const auto&) noexcept { current_tool->disable(); });
}




void EditorSelectionEnvironment::update() noexcept
{
    EditorEnvironment::update();

    negative_effect_.update();
}




void EditorSelectionEnvironment::draw() noexcept
{
    draw_selected_strokes();

    EditorEnvironment::draw();
}


void EditorSelectionEnvironment::draw_selected_strokes() noexcept
{
    if (editor.canvas.stroke_meshes.size() == 0)
        return;

    selection_outline_stroke_mesh_renderer_.outline_thickness = SelectionOutlineBaseThickness / editor.canvas.raylib_camera().zoom;

    negative_effect_.enable();
    editor.canvas.stroke_renderer.set_mesh_renderer(selection_outline_stroke_mesh_renderer_);
    editor.canvas.draw_strokes();
    editor.canvas.stroke_renderer.set_mesh_renderer(editor.default_stroke_mesh_renderer());
    negative_effect_.disable();
}




void EditorSelectionEnvironment::on_enabled() noexcept
{
    EditorEnvironment::on_enabled();

    editor.dynamic_background_color = false;
}