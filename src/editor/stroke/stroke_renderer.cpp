#include <blackboard/editor/stroke/stroke_renderer.hpp>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeRenderer;




void StrokeRenderer::draw_stroke_meshes(const std::vector<std::unique_ptr<StrokeMesh>>& meshes) noexcept
{
    for (const auto& mesh : meshes)
        draw_stroke_mesh(*mesh);
}


void StrokeRenderer::draw_stroke_meshes(const std::vector<StrokeMesh*>& meshes) noexcept
{
    for (const auto& mesh : meshes)
        draw_stroke_mesh(*mesh);
}


void StrokeRenderer::draw_stroke_meshes(const std::vector<StrokeMesh>& meshes) noexcept
{
    for (const auto& mesh : meshes)
        draw_stroke_mesh(mesh);
}