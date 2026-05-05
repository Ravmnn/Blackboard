#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>
#include <flustral/activatable.hpp>




class Canvas;


class CanvasCamera : public Activatable, public Updateable
{
private:
    Camera2D camera_;
    Camera2D target_camera_;


public:
    const Canvas& canvas;

    float min_zoom;
    float max_zoom;
    float zoom_factor;

    float movement_interpolation_velocity = 6;
    float zoom_interpolation_velocity = 5;
    float interpolation_smoothing = 0.01;


    void update() noexcept override;


    CanvasCamera(const Canvas& canvas, const float min_zoom, const float max_zoom, const float zoom_factor) noexcept;


    void enable() noexcept override { Activatable::enable(); BeginMode2D(camera_); }
    void disable() noexcept override { Activatable::disable(); EndMode2D(); }


    const Camera2D& camera() const noexcept { return camera_; }
    const Camera2D& target_camera() const noexcept { return target_camera_; }


private:
    void update_dragging() noexcept;
    void update_zoom() noexcept;
    void update_interpolation() noexcept;
};