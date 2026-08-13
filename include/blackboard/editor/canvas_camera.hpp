#pragma once

#include <blackboard/activatable.hpp>
#include <blackboard/bounds.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::editor
{




class Canvas;


class CanvasCamera : public Updateable, public Activatable, public Bounds
{
private:
    Camera2D camera_;
    Camera2D target_camera_;

    Vector2 mouse_delta_after_zoom_;

    animation::ExponentialInterpolation<Vector2> movement_interpolation_;
    animation::ExponentialInterpolation<float> zoom_interpolation_;


public:
    const Canvas& canvas;

    bool disable_zoom = false;
    bool disable_move = false;

    float min_zoom;
    float max_zoom;
    float zoom_factor;

    Vector2 bounds_expansion = {};


    CanvasCamera(const Canvas& canvas, float min_zoom, float max_zoom, float zoom_factor) noexcept;


    void update() noexcept override;


    void enable() noexcept override { Activatable::enable(); BeginMode2D(camera_); }
    void disable() noexcept override { Activatable::disable(); EndMode2D(); }


    [[nodiscard]] const Camera2D& camera() const noexcept { return camera_; }
    [[nodiscard]] const Camera2D& target_camera() const noexcept { return target_camera_; }
    [[nodiscard]] const Vector2& mouse_delta_after_zoom() const noexcept { return mouse_delta_after_zoom_; }


    [[nodiscard]] Rectangle bounding_box() const noexcept override;


private:
    void update_dragging() noexcept;
    void update_zoom() noexcept;
    void update_interpolation() noexcept;
};




}