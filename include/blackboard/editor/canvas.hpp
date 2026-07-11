#pragma once

#include <memory>

#include <blackboard/initializable.hpp>
#include <blackboard/mouse_position_provider.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/editor/canvas_camera.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class Canvas : public Updateable, public Initializable, public MousePositionProvider, public rendering::TextureRenderer
{
public:
    CanvasCamera camera;

    // TODO: move stroke rendering to editor
    std::vector<std::unique_ptr<StrokeMesh>> stroke_meshes;

    StrokeMeshGenerator stroke_mesh_generator;
    StrokeRenderer stroke_renderer;

    Color background_color;


    Canvas(const StrokeMeshRenderer& mesh_renderer) noexcept;


    void initialize() noexcept override;
    void update() noexcept override;


    [[nodiscard]] const Camera2D& raylib_camera() const noexcept { return camera.camera(); }

    [[nodiscard]] Vector2 mouse_delta() const noexcept override { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    [[nodiscard]] Vector2 mouse_position() const noexcept override { return map_point(screen_mouse_position()); }
    [[nodiscard]] Vector2 screen_mouse_position() const noexcept override { return GetMousePosition(); }


    [[nodiscard]] Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, camera.target_camera()); }


    void add_stroke(const Stroke& stroke) noexcept;


private:
    void resize_texture_renderer() noexcept;
};




}