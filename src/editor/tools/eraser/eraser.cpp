#include <blackboard/editor/tools/eraser/eraser.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>




using bb::editor::Eraser,
    bb::editor::StrokeMesh,
    bb::math::Segment;




Eraser::Eraser(Editor& editor) noexcept : Tool(editor),
    body(*this)
{}




void Eraser::update() noexcept
{
    Tool::update();

    if (active())
        update_strokes_to_remove();

    if (got_inactive_)
        remove_strokes_from_remove_queue();

    body.update();
    last_position_ = position();
}


void Eraser::update_strokes_to_remove() noexcept
{
    const Segment segment = { last_position_, this->position() };

    if (StrokeMesh* const stroke = get_canvas_stroke_intersecting_segment(segment))
        add_stroke_to_remove_queue(*stroke);
}


StrokeMesh* Eraser::get_canvas_stroke_intersecting_segment(const Segment& segment) noexcept
{
    for (auto& stroke : editor.canvas.stroke_meshes)
        if (StrokeMeshCollider::stroke_intersects_with_segment(*stroke, segment))
            return stroke.get();

    return nullptr;
}


void Eraser::add_stroke_to_remove_queue(StrokeMesh& stroke) noexcept
{
    for (auto& mesh_node : stroke)
        mesh_node.color.a = 150;

    strokes_to_remove_.push_back(&stroke);
}


void Eraser::remove_strokes_from_remove_queue() noexcept
{
    for (auto& stroke : strokes_to_remove_)
        remove_stroke(*stroke);

    strokes_to_remove_.clear();
}


void Eraser::remove_stroke(const StrokeMesh& stroke) noexcept
{
    std::erase_if(editor.canvas.stroke_meshes, [&](const std::unique_ptr<StrokeMesh>& stroke_mesh) {
        return stroke_mesh.get() == &stroke;
    });
}




void Eraser::draw() noexcept
{
    body.draw();
}




Vector2 Eraser::position() const noexcept
{
    return editor.canvas.mouse_position();
}