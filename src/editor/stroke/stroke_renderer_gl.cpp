#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>

#include <rlgl.h>

#include <blackboard/window.hpp>
#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>




using bb::editor::StrokeRendererGL;




StrokeRendererGL::StrokeRendererGL() noexcept
{
    coverage_.clear_on_enable = false;
    color_.clear_on_enable = false;
}




void StrokeRendererGL::update() noexcept
{
    if (!Window::resized())
        return;

    coverage_.resize(Window::size());
    color_.resize(Window::size());
}




void StrokeRendererGL::draw_composition() const noexcept
{
    coverage_.draw_y_inverted_texture_full();

    rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ZERO, RL_ONE, RL_FUNC_ADD, RL_FUNC_ADD);
    BeginBlendMode(BLEND_CUSTOM_SEPARATE);
    color_.draw_y_inverted_texture_full();
    EndBlendMode();
}


void StrokeRendererGL::clear_composition() noexcept
{
    coverage_.clear();
    color_.clear();
}




void StrokeRendererGL::draw_stroke_mesh(const StrokeMesh& mesh) noexcept
{
    draw_stroke_mesh_coverage(mesh);
    draw_stroke_mesh_color(mesh);
}




void StrokeRendererGL::draw_stroke_mesh_coverage(const StrokeMesh& mesh) noexcept
{
    rlSetBlendFactorsSeparate(RL_ZERO, RL_ZERO, RL_ONE, RL_ONE, RL_FUNC_ADD, RL_FUNC_ADD);
    BeginBlendMode(BLEND_CUSTOM_SEPARATE);

    coverage_.begin_render();
    draw_stroke_mesh_immediate(mesh);
    coverage_.end_render();

    EndBlendMode();
}


void StrokeRendererGL::draw_stroke_mesh_color(const StrokeMesh& mesh) noexcept
{
    rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ZERO, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
    BeginBlendMode(BLEND_CUSTOM_SEPARATE);

    color_.begin_render();
    draw_stroke_mesh_immediate(mesh);
    color_.end_render();

    EndBlendMode();
}




void StrokeRendererGL::draw_stroke_mesh_immediate(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGL mesh_gl = StrokeMeshGLBuilder().build(mesh);
    mesh_gl.load_gl_data();

    effect.enable();
    mesh_gl.draw();
    effect.disable();

    mesh_gl.unload_gl_data();
}