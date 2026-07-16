#pragma once

#include <optional>

#include <raylib.h>

#include <blackboard/rendering/effects/effect.hpp>




namespace bb::editor
{




class StrokeMeshQuad;
class StrokeMeshCapSegment;


class StrokeMeshRenderer
{
public:
    int primitive_shape_mode;
    std::optional<Color> overwrite_color;


    StrokeMeshRenderer() noexcept;
    virtual ~StrokeMeshRenderer() = default;


    virtual void render(const StrokeMeshQuad& quad) const noexcept;
    virtual void render(const StrokeMeshCapSegment& cap_segment) const noexcept;
};




};