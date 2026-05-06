#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




class Trail : public Stroke, public Updateable, public Drawable
{
private:
    StrokeRenderer trail_renderer_;


public:
    StrokePoint origin;
    float decay;
    bool emit = true;


    explicit Trail(const StrokePoint& origin, const float decay) noexcept;


    void update() noexcept override;
    void draw() noexcept override;
};