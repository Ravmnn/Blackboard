#pragma once

#include <flustral/updateable.hpp>
#include <flustral/drawable.hpp>

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