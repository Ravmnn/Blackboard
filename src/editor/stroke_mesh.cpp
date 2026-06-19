#include <blackboard/editor/stroke_mesh.hpp>




using bb::editor::StrokeMesh;




void StrokeMesh::set_color(const Color& color) noexcept
{
    for (auto& node : *this)
        node.color = color;
}


void StrokeMesh::set_alpha(const uint8_t alpha) noexcept
{
    for (auto& node : *this)
        node.color.a = alpha;
}