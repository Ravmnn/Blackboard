#pragma once

#include <vector>

#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/math/segment.hpp>




namespace bb::editor
{




class StrokeMeshCollider
{
public:
    static StrokeMesh* get_stroke_intersecting_segment(std::vector<StrokeMesh>& strokes, const math::Segment& segment) noexcept;
    static StrokeMesh* get_stroke_containing_point(std::vector<StrokeMesh>& strokes, const Vector2& point) noexcept;

    static bool stroke_intersects_with_segment(const StrokeMesh& stroke, const math::Segment& segment) noexcept;
    static bool stroke_contains_point(const StrokeMesh& stroke, const Vector2& point) noexcept;
};




}