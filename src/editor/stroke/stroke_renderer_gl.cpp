#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>

#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>
#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>




using bb::editor::StrokeRendererGL;




void StrokeRendererGL::draw_stroke_mesh(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGLBuilder mesh_gl_builder;
    mesh_gl_builder.cap_curvature = 0.2;

    StrokeMeshGL mesh_gl = mesh_gl_builder.build(mesh);

    effect.enable();
    mesh_gl.load_gl_data();

    mesh_gl.draw();

    mesh_gl.unload_gl_data();
    effect.disable();
}