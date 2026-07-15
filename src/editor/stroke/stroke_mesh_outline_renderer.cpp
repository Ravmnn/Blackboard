#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>

#include <raymath.h>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshOutlineRenderer;




void StrokeMeshOutlineRenderer::render(const StrokeMeshQuad& quad) const noexcept
{
    const Color color = overwrite_outline_color.value_or(quad.outline_color());
    const float thickness = overwrite_outline_thickness.value_or(quad.outline_thickness());

    if (thickness == 0)
        return;

    DrawLineEx(quad.top(), quad.next_top(), thickness, color);
    DrawLineEx(quad.bottom(), quad.next_bottom(), thickness, color);
}


void StrokeMeshOutlineRenderer::render(const StrokeMeshCapSegment& cap_segment) const noexcept
{
    const Color color = overwrite_outline_color.value_or(cap_segment.outline_color);
    const float thickness = overwrite_outline_thickness.value_or(cap_segment.outline_thickness);

    if (thickness == 0)
        return;

    DrawLineEx(
        Vector2MoveTowards(cap_segment.begin, cap_segment.end, -thickness / 5),
        Vector2MoveTowards(cap_segment.end, cap_segment.begin, -thickness / 5),
    thickness, color);
}