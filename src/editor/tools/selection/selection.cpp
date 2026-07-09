#include <blackboard/editor/tools/selection/selection.hpp>

#include <blackboard/math/collisions.hpp>
#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/editor_selection_environment.hpp>




using bb::editor::Selection,
    bb::math::Rect,
    bb::math::Collisions;




Selection::Selection(EditorEnvironment& environment) noexcept : Tool(environment),
    selection_environment(dynamic_cast<EditorSelectionEnvironment&>(environment)),
    body(*this)
{}




// TODO: add Tool::update_when_active
void Selection::update() noexcept
{
    if (active())
        update_selection();

    end_position_ = position();
    body.update();
}


void Selection::update_selection() noexcept
{
    selection_environment.in_selection_strokes_.clear();

    for (auto& stroke_mesh : editor().canvas.stroke_meshes)
        if (can_add_stroke_to_selection_list(*stroke_mesh))
            selection_environment.in_selection_strokes_.push_back(stroke_mesh.get());
}


size_t Selection::selected_mesh_nodes_for_stroke(const StrokeMesh& mesh) noexcept
{
    return std::ranges::count_if(mesh, [&](const auto& mesh_node) {
        return Collisions::point_inside_rectangle(mesh_node.position(), selection_area());
    });
}


bool Selection::can_add_stroke_to_selection_list(const StrokeMesh& mesh) noexcept
{
    return (float)selected_mesh_nodes_for_stroke(mesh) / (float)mesh.size() >= required_selection_ratio &&
        !std::ranges::contains(selection_environment.in_selection_strokes_, &mesh);
}




void Selection::draw() noexcept
{
    body.draw();
}




Vector2 Selection::position() const noexcept
{
    return editor().canvas.mouse_position();
}




void Selection::on_enabled() noexcept
{
    start_position_ = position();
}