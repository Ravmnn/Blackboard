#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>
#include <flustral/drawable.hpp>
#include <flustral/spring.hpp>
#include <flustral/rendering/texture_renderer.hpp>




class Brush;


class BrushBody : public Updateable, public Drawable
{
private:
    Spring<float> thickness_;
    Spring<float> stretch_;

    static constexpr float IdleThicknessVariation = 2;
    static constexpr float StretchSpeedFactor = 1.0 / 4.0;

    Color color_ = WHITE;
    Color color_target_ = WHITE;
    float color_interpolation_smoothing_ = 0.01;
    float color_interpolation_velocity_ = 2;

    static constexpr unsigned int NormalOpacity = 200;
    static constexpr unsigned int DrawingOpacity = 230;


    float last_rotation_ = 0;


public:
    Brush& brush;


    explicit BrushBody(Brush& brush) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_thickness() noexcept;
    void update_stretch() noexcept;
    void update_color() noexcept;


    void draw_rotated_stretched_ellipse(const Vector2& position, const float radius, const float stretch, const float rotation) noexcept;
};