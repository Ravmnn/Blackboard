#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke/stroke.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class Trail : public Stroke, public Updateable, public Drawable
{
private:
    StrokeMeshRenderer mesh_renderer_;
    StrokeRenderer trail_renderer_;
    StrokeMeshGenerator trail_mesh_generator_;


public:
    StrokePoint origin;
    float decay;
    bool emit = true;


    explicit Trail(const StrokePoint& origin, float decay) noexcept;


    void update() noexcept override;
    void draw() noexcept override;
};




}