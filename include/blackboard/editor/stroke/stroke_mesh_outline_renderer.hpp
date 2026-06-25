#pragma once

#include <blackboard/editor/stroke/stroke_mesh_renderer.hpp>




namespace bb::editor
{




class StrokeMeshOutlineRenderer : public StrokeMeshRenderer
{
public:
    float outline_thickness = 1.0f;


    void render(const StrokeMeshQuad& quad) const noexcept override;
    void render(const StrokeMeshCapSegment& cap_segment) const noexcept override;
};




}