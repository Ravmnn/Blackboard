#pragma once

#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/math/segment.hpp>




namespace bb::editor
{




class StrokeMeshCollider
{
public:
    static StrokeMesh* get_stroke_intersecting_segment(std::vector<StrokeMesh>& strokes, const math::Segment& segment) noexcept;
    static StrokeMesh* get_stroke_containing_point(std::vector<StrokeMesh>& strokes, const Vector2& point) noexcept;

    static StrokeMeshNode* get_stroke_mesh_node_colliding_with_point(StrokeMesh& stroke, const Vector2& point, float radius = 4) noexcept;
    static StrokeMeshNode* get_stroke_mesh_node_segment_colliding_with_point(StrokeMesh& stroke, const Vector2& point) noexcept;
    static StrokeMeshNode* get_stroke_mesh_node_intersecting_with_segment(StrokeMesh& stroke, const math::Segment& segment) noexcept;

    static bool stroke_intersects_with_segment(StrokeMesh& stroke, const math::Segment& segment) noexcept {
        return get_stroke_mesh_node_intersecting_with_segment(stroke, segment);
    }

    static bool stroke_contains_point(StrokeMesh& stroke, const Vector2& point) noexcept {
        return get_stroke_mesh_node_segment_colliding_with_point(stroke, point);
    }
};




}