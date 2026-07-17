#include <blackboard/editor/stroke/stroke_mesh_manager.hpp>

#include <cassert>




using bb::editor::StrokeMeshManager,
    bb::editor::StrokeMesh;




StrokeMeshManager::StrokeMeshManager(StrokeRenderer& renderer) noexcept :
    generator(6),
    renderer(&renderer)
{}




void StrokeMeshManager::draw() noexcept
{
    if (renderer)
        renderer->draw_stroke_meshes(meshes);
}


void StrokeMeshManager::draw_stroke(const Stroke& stroke) const noexcept
{
    const auto mesh = generator.generate_mesh(stroke);

    if (mesh)
        draw_stroke_mesh(*mesh);
}


void StrokeMeshManager::draw_stroke_mesh(const StrokeMesh& mesh) const noexcept
{
    if (renderer)
        renderer->draw_stroke_mesh(mesh);
}




void StrokeMeshManager::add_stroke(const Stroke& stroke) noexcept
{
    auto mesh = generator.generate_mesh(stroke);

    if (mesh)
        meshes.push_back(std::move(mesh));
}


void StrokeMeshManager::remove_mesh(const StrokeMesh& mesh) noexcept
{
    std::erase_if(meshes, [&](const std::unique_ptr<StrokeMesh>& stroke_mesh) {
        return stroke_mesh.get() == &mesh;
    });
}