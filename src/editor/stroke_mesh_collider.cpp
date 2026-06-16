#include <blackboard/editor/stroke_mesh_collider.hpp>

#include <blackboard/math/segment.hpp>




using bb::editor::StrokeMeshCollider,
    bb::editor::StrokeMesh,
    bb::math::Segment;




StrokeMesh* StrokeMeshCollider::get_stroke_containing_point(std::vector<StrokeMesh>& meshes, const Vector2& point) noexcept
{
    for (auto& mesh : meshes)
    {
        if (mesh.size() < 2)
            continue;

        for (size_t i = 0; i < mesh.size() - 1; i++)
        {
            const Vector2 start = mesh[i].position();
            const Vector2 end = mesh[i + 1].position();

            const float half_thickness = mesh[i].half_thickness();

            if (Segment::is_point_in_segment(start, end, point, half_thickness))
                return &mesh;
        }
    }


    return nullptr;
}