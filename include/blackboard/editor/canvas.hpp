#pragma once

#include <blackboard/rendering/renderizable.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/palette.hpp>
#include <blackboard/editor/canvas_camera.hpp>
#include <blackboard/mouse_position_provider.hpp>
#include <blackboard/editor/canvas_renderer.hpp>




namespace bb::editor
{




class Canvas : public Updateable, public Drawable, public MousePositionProvider
{
public:
    static constexpr Color DefaultBackgroundColor = Color{ 18, 18, 18, 255 };


private:
    std::vector<StrokeMesh> stroke_meshes_;

    animation::LinearInterpolation<Color> background_color_;

    bool initialized_ = false;


public:
    // TODO: create logic for stroke mouse collision

    CanvasRenderer canvas_renderer;
    CanvasCamera camera;

    StrokeMeshGenerator stroke_mesh_generator;
    StrokeRenderer stroke_renderer;

    Palette palette;
    bool dynamic_background_color = true;

    Brush brush;
    Eraser eraser;

    Tool* current_tool = nullptr;


    Canvas(const Palette& palette);


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] const Camera2D& raylib_camera() const noexcept { return camera.camera(); }
    [[nodiscard]] const std::vector<StrokeMesh>& stroke_meshes() const noexcept { return stroke_meshes_; }
    [[nodiscard]] const Color& background_color() const noexcept { return background_color_.current; }

    [[nodiscard]] Vector2 mouse_delta() const noexcept override { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    [[nodiscard]] Vector2 mouse_position() const noexcept override { return map_point(screen_mouse_position()); }
    [[nodiscard]] Vector2 screen_mouse_position() const noexcept override { return GetMousePosition() * CanvasRenderer::SuperSamplingFactor; }


    [[nodiscard]] Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, camera.target_camera()); }


    void add_stroke(const Stroke& stroke) noexcept;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }

    void alternate_tool() noexcept { current_tool = current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


private:
    void initialize() noexcept;
    void recreate_texture_renderer() noexcept;

    void update_background_color() noexcept;


    void draw_content() noexcept;

    void draw_strokes() noexcept;
};




}