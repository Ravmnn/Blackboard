#pragma once

#include <blackboard/editor/stroke_mesh.hpp>




namespace bb::editor
{




class StrokeMeshCollider
{
public:
    static StrokeMesh* get_stroke_containing_point(std::vector<StrokeMesh>& meshes, const Vector2& point) noexcept;
};




}