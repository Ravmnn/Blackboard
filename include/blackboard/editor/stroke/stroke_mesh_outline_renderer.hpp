#pragma once

#include <blackboard/editor/stroke/stroke_mesh_renderer.hpp>




namespace bb::editor
{




class StrokeMeshOutlineRenderer : public StrokeMeshRenderer
{
public:
    std::optional<Color> overwrite_outline_color;
    std::optional<float> overwrite_outline_thickness;


    void render(const StrokeMeshQuad& quad) const noexcept override;
    void render(const StrokeMeshCapSegment& cap_segment) const noexcept override;
};




}