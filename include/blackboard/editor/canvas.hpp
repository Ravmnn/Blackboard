#pragma once

#include <blackboard/rendering/renderizable.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/stroke_renderer.hpp>
#include <blackboard/editor/canvas_camera.hpp>
#include <blackboard/editor/mouse_position_provider.hpp>




class Canvas : public Updateable, public Drawable, public MousePositionProvider
{
public:
    static constexpr Color DefaultBackgroundColor = Color{ 18, 18, 18, 255 };
    static constexpr Color DefaultBrushColor = Color{ 211, 211, 211, 255 };


private:
    TextureRenderer super_sampled_texture_;
    TextureRenderer final_texture_;

    std::vector<StrokeMesh> stroke_meshes_;

    bool initialized_ = false;


public:
    static constexpr float SuperSamplingFactor = 4;


    StrokeMeshGenerator stroke_mesh_generator;
    StrokeRenderer stroke_renderer;

    CanvasCamera canvas_camera;

    Brush brush;
    Eraser eraser;

    Tool* current_tool = nullptr;

    Color background_color = DefaultBackgroundColor;


    Canvas();


    void update() noexcept override;
    void draw() noexcept override;


    const Camera2D& camera() const noexcept { return canvas_camera.camera(); }
    const std::vector<StrokeMesh>& stroke_meshes() const noexcept { return stroke_meshes_; }

    Vector2 mouse_delta() const noexcept override { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    Vector2 mouse_position() const noexcept override { return map_point(screen_mouse_position()); }
    Vector2 screen_mouse_position() const noexcept override { return GetMousePosition() * SuperSamplingFactor; }


    Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, canvas_camera.target_camera()); }


    void add_stroke(const Stroke& stroke) noexcept;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }

    void alternate_tool() noexcept { current_tool = current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


private:
    void initialize() noexcept;
    void recreate_texture_renderer() noexcept;


    void draw_to_super_sampled_texture() noexcept;
    void draw_super_sampled_to_final_texture() noexcept;

    void draw_strokes() noexcept;
    void draw_super_sampled_contents() noexcept;
};