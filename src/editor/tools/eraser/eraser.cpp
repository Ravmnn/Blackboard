#include <blackboard/editor/tools/eraser/eraser.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>




using bb::editor::Eraser,
    bb::editor::StrokeMesh;




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

    iteration_amount_test_ = get_iteration_amount();

    body.update();
    last_position_ = position();
}


void Eraser::update_strokes_to_remove() noexcept
{
    const Vector2 position = this->position();
    const auto final_iteration_amount = get_iteration_amount();

    for (size_t i = 0; i < final_iteration_amount; i++)
    {
        const Vector2 point = Vector2Lerp(last_position_, position, (float)i / (float)iteration_amount);

        if (StrokeMesh* const stroke = get_canvas_stroke_at_point(point))
            add_stroke_to_remove_queue(*stroke);
    }
}


StrokeMesh* Eraser::get_canvas_stroke_at_point(const Vector2& point) noexcept
{
    for (auto& stroke : editor_.canvas.stroke_meshes)
        if (StrokeMeshCollider::stroke_contains_point(*stroke, point)) // TODO: use segment-segment intersection instead of point collision
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
    std::erase_if(editor_.canvas.stroke_meshes, [&](const std::unique_ptr<StrokeMesh>& stroke_mesh) {
        return stroke_mesh.get() == &stroke;
    });
}




void Eraser::draw() noexcept
{
    body.draw();
}




Vector2 Eraser::position() const noexcept
{
    return editor_.canvas.mouse_position();
}