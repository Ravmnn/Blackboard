#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>

#include <blackboard/math/segment.hpp>




using bb::editor::StrokeMeshCollider,
    bb::editor::StrokeMesh,
    bb::math::Segment;




StrokeMesh* StrokeMeshCollider::get_stroke_containing_point(std::vector<StrokeMesh>& strokes, const Vector2& point) noexcept
{
    for (auto& stroke : strokes)
        if (stroke_contains_point(stroke, point))
            return &stroke;

    return nullptr;
}


bool StrokeMeshCollider::stroke_contains_point(const StrokeMesh& stroke, const Vector2& point) noexcept
{
    if (stroke.size() < 2)
        return false;

    for (size_t i = 0; i < stroke.size() - 1; i++)
    {
        const Vector2 start = stroke[i].position();
        const Vector2 end = stroke[i + 1].position();
        const float half_thickness = stroke[i].half_thickness();

        if (Segment::is_point_in_segment(start, end, point, half_thickness))
            return true;
    }

    return false;
}