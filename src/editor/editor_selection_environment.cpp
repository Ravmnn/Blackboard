#include <blackboard/editor/editor_selection_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorSelectionEnvironment;




EditorSelectionEnvironment::EditorSelectionEnvironment(Editor& editor) noexcept : EditorEnvironment(editor)
{
    negative_effect_.default_color = RED;
}




void EditorSelectionEnvironment::update() noexcept
{
    negative_effect_.update();
}




void EditorSelectionEnvironment::draw() noexcept
{
    draw_selected_strokes();
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