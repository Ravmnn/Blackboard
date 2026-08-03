#pragma once

#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/editor/effects/stroke.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class StrokeRendererGL : public StrokeRenderer
{
private:
    rendering::TextureRenderer coverage_;
    rendering::TextureRenderer color_;


public:
    StrokeEffect effect;


    StrokeRendererGL() noexcept;


    void draw_composition() const noexcept;
    void clear_composition() noexcept;


    void draw_stroke_mesh(const StrokeMesh& mesh) noexcept override;
    void draw_stroke_mesh_immediate(const StrokeMesh& mesh) noexcept;


private:
    void draw_stroke_mesh_coverage(const StrokeMesh& mesh) noexcept;
    void draw_stroke_mesh_color(const StrokeMesh& mesh) noexcept;
};




}