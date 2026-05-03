#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>




class CanvasCamera : public Updateable
{
private:
    Camera2D camera_;
    Camera2D target_camera_;


public:
    float min_zoom;
    float max_zoom;
    float zoom_factor;

    float interpolation_velocity = 4;
    float interpolation_smoothing = 0.01;


    void update() noexcept override;


    CanvasCamera(const float min_zoom, const float max_zoom, const float zoom_factor) noexcept;


    const Camera2D& camera() const noexcept { return camera_; }


private:
    void update_dragging() noexcept;
    void update_zoom() noexcept;
    void update_interpolation() noexcept;
};