#include <blackboard/editor/stroke/stroke_mesh_manager.hpp>




using bb::editor::StrokeMeshManager,
    bb::editor::StrokeMesh;




StrokeMeshManager::StrokeMeshManager() noexcept :
    generator(6),
    renderer(default_mesh_renderer)
{}




void StrokeMeshManager::draw() noexcept
{
    renderer.draw_stroke_meshes(meshes);
}


void StrokeMeshManager::draw_stroke(const Stroke& stroke) noexcept
{
    const auto mesh = generator.generate_mesh(stroke);

    if (mesh)
        renderer.draw_stroke_mesh(*mesh);
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