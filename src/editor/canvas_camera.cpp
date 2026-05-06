#include <blackboard/editor/canvas_camera.hpp>

#include <raymath.h>

#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/canvas.hpp>




CanvasCamera::CanvasCamera(const Canvas& canvas, const float min_zoom, const float max_zoom, const float zoom_factor) noexcept :
    canvas(canvas), min_zoom(min_zoom), max_zoom(max_zoom), zoom_factor(zoom_factor)
{
    target_camera_ = {
        .target = 0,
        .rotation = 0,
        .zoom = canvas.SuperSamplingFactor
    };

    camera_ = target_camera_;

    movement_interpolation_ = Interpolation(target_camera_.target, 0.01, 6);
    zoom_interpolation_ = Interpolation(target_camera_.zoom, 0.01, 5);
}




void CanvasCamera::update() noexcept
{
    camera_.offset = target_camera_.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

    update_dragging();
    update_zoom();
    update_interpolation();
}


void CanvasCamera::update_dragging() noexcept
{
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        target_camera_.target += GetMouseDelta() * canvas.SuperSamplingFactor / target_camera_.zoom * -1;
}


void CanvasCamera::update_zoom() noexcept
{
    if (!GetMouseWheelMove())
        return;

    const Vector2 mouse_world = canvas.mouse_position();
    target_camera_.zoom += GetMouseWheelMove() * target_camera_.zoom * zoom_factor;
    target_camera_.zoom = Clamp(target_camera_.zoom, min_zoom, max_zoom);

    const Vector2 mouse_world_after = canvas.mouse_position();
    target_camera_.target.x += mouse_world.x - mouse_world_after.x;
    target_camera_.target.y += mouse_world.y - mouse_world_after.y;
}


void CanvasCamera::update_interpolation() noexcept
{
    camera_.target = movement_interpolation_.set_target_and_update(target_camera_.target);
    camera_.zoom = zoom_interpolation_.set_target_and_update(target_camera_.zoom);
}