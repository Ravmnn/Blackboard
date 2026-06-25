#pragma once

#include <optional>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




namespace bb::editor
{




class StrokeMeshRenderer
{
public:
    int primitive_shape_mode;
    std::optional<Color> overwrite_color;


    StrokeMeshRenderer() noexcept;


    virtual void render(const StrokeMeshQuad& quad) const noexcept;
    virtual void render(const StrokeMeshCapSegment& cap_segment) const noexcept;
};




};