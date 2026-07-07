#pragma once

#include <vector>

#include <raylib.h>




namespace bb::editor
{




class StrokeMesh;


class StrokeMeshCollider
{
public:
    static StrokeMesh* get_stroke_containing_point(std::vector<StrokeMesh>& strokes, const Vector2& point) noexcept;
    static bool stroke_contains_point(const StrokeMesh& stroke, const Vector2& point) noexcept;
};




}