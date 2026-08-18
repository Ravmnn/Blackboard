#pragma once

#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/editor/effects/stroke.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class StrokeMeshGL;


class StrokeRendererGL : public StrokeRenderer, public Updateable
{
private:
    rendering::TextureRenderer coverage_;
    rendering::TextureRenderer color_;


public:
    StrokeEffect effect;


    StrokeRendererGL() noexcept;


    void update() noexcept override;


    void draw_composition() const noexcept;
    void clear_composition() noexcept;


    void draw_stroke_mesh(const StrokeMesh& mesh) noexcept override;
    void draw_stroke_mesh_gl(StrokeMeshGL& mesh) noexcept;
    void draw_stroke_mesh_gl_immediate(StrokeMeshGL& mesh) noexcept;


private:
    void draw_stroke_mesh_gl_coverage(StrokeMeshGL& mesh) noexcept;
    void draw_stroke_mesh_gl_color(StrokeMeshGL& mesh) noexcept;
};




}