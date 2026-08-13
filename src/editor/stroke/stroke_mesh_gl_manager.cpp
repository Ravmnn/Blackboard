#include <blackboard/editor/stroke/stroke_mesh_gl_manager.hpp>

#include <cassert>




using
bb::editor::StrokeMeshGLManager,
bb::editor::StrokeRendererGL;




StrokeMeshGLManager::StrokeMeshGLManager(StrokeRendererGL& renderer) noexcept
    : editor::StrokeMeshManager(renderer)
{}




void StrokeMeshGLManager::draw_composition() const noexcept
{
    assert(renderer_as_gl());
    renderer_as_gl()->draw_composition();
}


void StrokeMeshGLManager::clear_composition() const noexcept
{
    assert(renderer_as_gl());
    renderer_as_gl()->clear_composition();
}