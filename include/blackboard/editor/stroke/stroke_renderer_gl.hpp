#pragma once

#include <blackboard/editor/effects/stroke.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class StrokeRendererGL : public StrokeRenderer
{
public:
    StrokeEffect effect;


    void draw_stroke_mesh(const StrokeMesh& mesh) noexcept override;
};




}