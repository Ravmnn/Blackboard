#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>




using
bb::math::Segment,
bb::editor::StrokeMesh,
bb::editor::StrokeMeshCollider;




StrokeMesh* StrokeMeshCollider::get_stroke_intersecting_segment(std::vector<StrokeMesh>& strokes, const math::Segment& segment) noexcept
{
    for (auto& stroke : strokes)
        if (stroke_intersects_with_segment(stroke, segment))
            return &stroke;

    return nullptr;
}


StrokeMesh* StrokeMeshCollider::get_stroke_containing_point(std::vector<StrokeMesh>& strokes, const Vector2& point) noexcept
{
    for (auto& stroke : strokes)
        if (stroke_contains_point(stroke, point))
            return &stroke;

    return nullptr;
}




bool StrokeMeshCollider::stroke_intersects_with_segment(const StrokeMesh& stroke, const math::Segment& segment) noexcept
{
    if (stroke.size() < 2)
        return false;

    for (size_t i = 0; i < stroke.size() - 1; i++)
        if (Segment::intersects({ stroke[i].position(), stroke[i + 1].position() }, segment))
            return true;

    return false;
}


bool StrokeMeshCollider::stroke_contains_point(const StrokeMesh& stroke, const Vector2& point) noexcept
{
    if (stroke.size() < 2)
        return false;

    for (size_t i = 0; i < stroke.size() - 1; i++)
        if (Segment::is_point_in_segment({ stroke[i].position(), stroke[i + 1].position() }, point, stroke[i].half_thickness()))
            return true;

    return false;
}