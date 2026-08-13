#include <blackboard/editor/canvas_camera.hpp>

#include <blackboard/editor/canvas.hpp>




using
bb::animation::ExponentialInterpolation,
bb::editor::CanvasCamera;




CanvasCamera::CanvasCamera(const Canvas& canvas, const float min_zoom, const float max_zoom, const float zoom_factor) noexcept :
    movement_interpolation_(target_camera_.target, 6),
    zoom_interpolation_(target_camera_.zoom, 5),

    canvas(canvas),
    min_zoom(min_zoom),
    max_zoom(max_zoom),
    zoom_factor(zoom_factor)
{
    target_camera_ = Camera2D{
        .target = {},
        .rotation = 0,
        .zoom = 1
    };

    camera_ = target_camera_;
}




void CanvasCamera::update() noexcept
{
    camera_.offset = target_camera_.offset = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };

    update_dragging();
    update_zoom();
    update_interpolation();
}


void CanvasCamera::update_dragging() noexcept
{
    if (disable_move)
        return;

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        target_camera_.target += MousePositionProvider::screen().mouse_delta() / target_camera_.zoom * -1;
}


void CanvasCamera::update_zoom() noexcept
{
    if (disable_zoom || GetMouseWheelMove() == 0)
        return;

    const Vector2 mouse_world = canvas.mouse_position();
    target_camera_.zoom += GetMouseWheelMove() * target_camera_.zoom * zoom_factor;
    target_camera_.zoom = Clamp(target_camera_.zoom, min_zoom, max_zoom);

    const Vector2 mouse_world_after = canvas.mouse_position();
    mouse_delta_after_zoom_ = mouse_world - mouse_world_after;
    target_camera_.target += mouse_delta_after_zoom_;
}


void CanvasCamera::update_interpolation() noexcept
{
    camera_.target = movement_interpolation_.set_target_and_update(target_camera_.target);
    camera_.zoom = zoom_interpolation_.set_target_and_update(target_camera_.zoom);
}




Rectangle CanvasCamera::bounding_box() const noexcept
{
    const Vector2 screen_size = Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() };

    const Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, camera_) - bounds_expansion;
    const Vector2 bottomRight = GetScreenToWorld2D(screen_size, camera_) + bounds_expansion * 2;

    return Rectangle { topLeft.x, topLeft.y, bottomRight.x - topLeft.x, bottomRight.y - topLeft.y };
}