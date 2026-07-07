#include <blackboard/editor/stroke/stroke_mesh_renderer.hpp>

#include <rlgl.h>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshRenderer;




StrokeMeshRenderer::StrokeMeshRenderer() noexcept :
    primitive_shape_mode(RL_QUADS)
{}




void StrokeMeshRenderer::render(const StrokeMeshQuad& quad) const noexcept
{
    const Color color = overwrite_color.value_or(quad.color());

    rlBegin(primitive_shape_mode);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlVertex2f(quad.top().x, quad.top().y);
    rlVertex2f(quad.next_top().x, quad.next_top().y);
    rlVertex2f(quad.next_bottom().x, quad.next_bottom().y);
    rlVertex2f(quad.bottom().x, quad.bottom().y);

    rlEnd();
}


void StrokeMeshRenderer::render(const StrokeMeshCapSegment& cap_segment) const noexcept
{
    const Color& color = overwrite_color.value_or(cap_segment.color);
    DrawTriangle(cap_segment.center, cap_segment.begin, cap_segment.end, color);
}