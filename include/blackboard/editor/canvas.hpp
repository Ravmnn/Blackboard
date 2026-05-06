#pragma once

#include <array>

#include <flustral/drawable.hpp>
#include <flustral/rendering/window_renderer.hpp>

#include <blackboard/editor/brush.hpp>
#include <blackboard/editor/eraser.hpp>
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
    Eraser eraser;



    Tool* active_tool = nullptr;

    std::vector<Stroke> drawn_strokes;


    Canvas();


    void update() noexcept override;
    void draw() noexcept override;


    const Camera2D camera() const noexcept { return canvas_camera_.camera(); }
    const Color& background_color() const noexcept { return background_color_; }


    Vector2 mouse_delta() const noexcept { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    Vector2 mouse_position() const noexcept { return map_point(screen_mouse_position()); }

    Vector2 screen_mouse_position() const noexcept { return GetMousePosition() * SuperSamplingFactor; }


    Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, canvas_camera_.target_camera()); }


    void set_current_tool(Tool& tool) noexcept { active_tool = &tool; }

    void alternate_tool() noexcept { active_tool = active_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


private:
    void initialize() noexcept;
    void recreate_texture_renderer() noexcept;

    void update_tool_switch() noexcept;


    void draw_strokes() noexcept;
    void draw_antialiased_contents() noexcept;
};