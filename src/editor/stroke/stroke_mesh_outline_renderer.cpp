#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshOutlineRenderer;




void StrokeMeshOutlineRenderer::render(const StrokeMeshQuad& quad) const noexcept
{
    const Color color = overwrite_color.value_or(quad.color());

    DrawLineEx(quad.top(), quad.next_top(), outline_thickness, color);
    DrawLineEx(quad.bottom(), quad.next_bottom(), outline_thickness, color);
}


void StrokeMeshOutlineRenderer::render(const StrokeMeshCapSegment& cap_segment) const noexcept
{
    const Color color = overwrite_color.value_or(cap_segment.color);

    DrawLineEx(
        Vector2MoveTowards(cap_segment.begin, cap_segment.end, -outline_thickness / 5),
        Vector2MoveTowards(cap_segment.end, cap_segment.begin, -outline_thickness / 5),
    outline_thickness, color);
}