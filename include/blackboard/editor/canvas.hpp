#pragma once

#include <flustral/drawable.hpp>

#include <blackboard/editor/brush.hpp>
#include <blackboard/editor/stroke_renderer.hpp>
#include <blackboard/editor/canvas_camera.hpp>




class Canvas : public Updateable, public Drawable
{
private:
    StrokeRenderer stroke_renderer_;
    CanvasCamera canvas_camera_;

    Color background_color_ = Color{ 15, 15, 15 };


public:
    Brush brush;
    std::vector<Stroke> strokes;


    Canvas();


    void update() noexcept override;
    void draw() noexcept override;


    const Camera2D camera() const noexcept { return canvas_camera_.camera(); }

    const Color& background_color() const noexcept { return background_color_; }
};