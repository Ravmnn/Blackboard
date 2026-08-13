#pragma once

#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>
#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>




namespace bb::editor
{




class Trail : public Stroke, public Updateable, public Drawable
{
private:
    StrokeRendererGL trail_renderer_;
    StrokeMeshGenerator trail_mesh_generator_;


public:
    const Camera2D& camera;

    StrokePoint origin;
    float decay;
    bool emit = true;


    explicit Trail(const Camera2D& camera, const StrokePoint& origin, float decay) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_points_decayment() noexcept;
    void update_renderer() noexcept;

    void remove_points_with_no_thickness() noexcept;
};




}