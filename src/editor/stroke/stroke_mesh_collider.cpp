#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>

#include <blackboard/math/collisions.hpp>




using
bb::math::Segment,
bb::math::Collisions,
bb::editor::StrokeMesh,
bb::editor::StrokeMeshNode,
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




StrokeMeshNode* StrokeMeshCollider::get_stroke_mesh_node_colliding_with_point(StrokeMesh& stroke, const Vector2& point, const float radius) noexcept
{
    if (stroke.empty())
        return nullptr;

    for (auto& node : stroke)
        if (Collisions::point_inside_circle(point, node.position(), radius))
            return &node;

    return nullptr;
}


StrokeMeshNode* StrokeMeshCollider::get_stroke_mesh_node_segment_colliding_with_point(StrokeMesh& stroke, const Vector2& point) noexcept
{
    if (stroke.size() < 2)
        return nullptr;

    for (size_t i = 0; i < stroke.size() - 1; i++)
        if (Segment::is_point_in_segment({ stroke[i].position(), stroke[i + 1].position() }, point, stroke[i].half_thickness()))
            return &stroke[i];

    return nullptr;
}


StrokeMeshNode* StrokeMeshCollider::get_stroke_mesh_node_intersecting_with_segment(StrokeMesh& stroke, const math::Segment& segment) noexcept
{
    if (stroke.size() < 2)
        return nullptr;

    for (size_t i = 0; i < stroke.size() - 1; i++)
        if (Segment::intersects({ stroke[i].position(), stroke[i + 1].position() }, segment))
            return &stroke[i];

    return nullptr;
}