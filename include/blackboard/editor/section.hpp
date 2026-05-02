#pragma once

#include <vector>

#include <blackboard/editor/spline_segment.hpp>




class Section : public Drawable
{
private:
    RenderTexture _texture;


public:
    const std::vector<SplineSegment> segments;


    Section(const std::vector<SplineSegment>& segments) noexcept
        : segments(segments) {}


    void draw() noexcept override {  }
};