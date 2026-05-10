#pragma once

#include <blackboard/rendering/window_renderer.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/stroke_renderer.hpp>
#include <blackboard/editor/canvas_camera.hpp>
#include <blackboard/editor/mouse_button_event.hpp>
#include <blackboard/editor/mouse_position_provider.hpp>




class Canvas : public Updateable, public Drawable, public MousePositionProvider
{
public:
    static constexpr Color DefaultBackgroundColor = Color{ 18, 18, 18, 255 };
    static constexpr Color DefaultBrushColor = Color{ 211, 211, 211, 255 };


private:
    StrokeMeshGenerator stroke_mesh_generator_;
    StrokeRenderer stroke_renderer_;

    CanvasCamera canvas_camera_;

    WindowRenderer window_renderer_;
    TextureRenderer texture_renderer_;

    std::vector<StrokeMesh> stroke_meshes_;
    Color background_color_ = DefaultBackgroundColor;

    bool initialized_ = false;

    bool draw_statistics_ = false;


    MouseButtonEvent left_button_ = MouseButtonEvent(MOUSE_BUTTON_LEFT, *this);
    MouseButtonEvent aux_button_ = MouseButtonEvent(MOUSE_BUTTON_RIGHT, *this);


public:
    static constexpr float SuperSamplingFactor = 4;


    Brush brush;
    Eraser eraser;


    Tool* current_tool = nullptr;


    Canvas();


    void update() noexcept override;
    void draw() noexcept override;


    const CanvasCamera& canvas_camera() const noexcept { return canvas_camera_; }
    const Camera2D& camera() const noexcept { return canvas_camera_.camera(); }
    const std::vector<StrokeMesh>& stroke_meshes() const noexcept { return stroke_meshes_; }
    const Color& background_color() const noexcept { return background_color_; }

    Vector2 mouse_delta() const noexcept override { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    Vector2 mouse_position() const noexcept override { return map_point(screen_mouse_position()); }
    Vector2 screen_mouse_position() const noexcept override { return GetMousePosition() * SuperSamplingFactor; }


    Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, canvas_camera_.target_camera()); }


    void add_stroke(const Stroke& stroke) noexcept;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }

    void alternate_tool() noexcept { current_tool = current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


private:
    void initialize() noexcept;
    void recreate_texture_renderer() noexcept;

    void update_input() noexcept;
    void update_mouse_buttons() noexcept;


    void draw_to_buffer_texture() noexcept;
    void draw_buffer_texture_to_window() noexcept;

    void draw_strokes() noexcept;
    void draw_antialiased_contents() noexcept;
    void draw_statistics() noexcept;
};