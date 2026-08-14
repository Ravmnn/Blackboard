#pragma once

#include <blackboard/initializable.hpp>
#include <blackboard/math/rect.hpp>
#include <blackboard/mouse_position_provider.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/ui/clickable.hpp>
#include <blackboard/ui/components/component.hpp>
#include <blackboard/editor/canvas_camera.hpp>




namespace bb::editor
{




class Stroke;


class Canvas : public ui::Component, public ui::Clickable, public Initializable, public MousePositionProvider, public rendering::TextureRenderer
{
public:
    MouseButtonEvent middle_button;

    CanvasCamera camera;


    Canvas(Component* parent) noexcept;


    void initialize() noexcept override;
    void update() noexcept override;


    [[nodiscard]] const Camera2D& raylib_camera() const noexcept { return camera.camera(); }

    [[nodiscard]] Vector2 mouse_delta() const noexcept override { return map_point(GetMousePosition()) - map_point(GetMousePosition() - GetMouseDelta()); }
    [[nodiscard]] Vector2 mouse_position() const noexcept override { return map_point(screen_mouse_position()); }
    [[nodiscard]] Vector2 screen_mouse_position() const noexcept override { return GetMousePosition(); }

    [[nodiscard]] bool is_point_over(const Vector2& /* unused */) const noexcept override { return true; }

    [[nodiscard]] Vector2 map_point(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, camera.target_camera()); }
    [[nodiscard]] Vector2 map_point_using_interpolated_camera(const Vector2& point) const noexcept { return GetScreenToWorld2D(point, camera.camera()); }


    [[nodiscard]] Rectangle bounding_box() const noexcept override {
        return math::Rect::from_position_and_size(absolute_position(), resolution());
    }


private:
    void draw_self() noexcept override;


    void resize_texture_renderer() noexcept;
};




}