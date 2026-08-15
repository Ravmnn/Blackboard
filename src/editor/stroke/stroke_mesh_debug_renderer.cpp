#include <blackboard/editor/stroke/stroke_mesh_debug_renderer.hpp>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshDebugRenderer;




void StrokeMeshDebugRenderer::draw(const StrokeMesh& mesh) const noexcept
{
    for (const auto& node : mesh)
    {
        if (draw_points)
            debug_draw_point(node);

        if (draw_samples)
            debug_draw_sample(node);

        if (draw_edges)
            debug_draw_edge(node);
    }
}




void StrokeMeshDebugRenderer::debug_draw_point(const StrokeMeshNode& node) noexcept
{
    DrawCircleV(node.sample.interpolation.origin_point, DebugCircleRadius, RED);
}


void StrokeMeshDebugRenderer::debug_draw_sample(const StrokeMeshNode& node) noexcept
{
    DrawCircleV(node.position(), DebugCircleRadius, BLUE);
}


void StrokeMeshDebugRenderer::debug_draw_edge(const StrokeMeshNode& node) noexcept
{
    DrawCircleV(node.edge.top, DebugCircleRadius, BLUE);
    DrawCircleV(node.edge.bottom, DebugCircleRadius, BLUE);
}