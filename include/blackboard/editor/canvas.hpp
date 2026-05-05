#pragma once

#include <flustral/drawable.hpp>
#include <flustral/rendering/window_renderer.hpp>

#include <blackboard/editor/brush.hpp>
#include <blackboard/editor/stroke_renderer.hpp>
#include <blackboard/editor/canvas_camera.hpp>




class Canvas : public Updateable, public Drawable
{
private:
    StrokeRenderer stroke_renderer_;
    CanvasCamera canvas_camera_;

    WindowRenderer window_renderer_;
    TextureRenderer texture_renderer_;

    Color background_color_ = Color{ 18, 18, 18, 255 };

    bool initialized_ = false;


public:
    static constexpr float SuperSamplingFactor = 4;


    Brush brush;
    std::vector<Stroke> drawn_strokes;


    Canvas();


    void update() noexcept override;
    void draw() noexcept override;


    const Camera2D camera() const noexcept { return canvas_camera_.camera(); }

    const Color& background_color() const noexcept { return background_color_; }


    Vector2 mouse_position() const noexcept { return GetScreenToWorld2D(screen_mouse_position(), canvas_camera_.target_camera()); }
    Vector2 screen_mouse_position() const noexcept { return GetMousePosition() * SuperSamplingFactor; }


private:
    void initialize() noexcept;

    void recreate_texture_renderer() noexcept;


    void update_drawing() noexcept;


    void draw_strokes() noexcept;
    void draw_antialiased_contents() noexcept;
};