#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>

#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>




using bb::editor::StrokeRendererGL;




void StrokeRendererGL::draw_stroke_mesh(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGL mesh_gl = StrokeMeshGL::from_stroke(mesh);

    effect.enable();
    mesh_gl.load_gl_data();

    mesh_gl.draw();

    mesh_gl.unload_gl_data();
    effect.disable();
}