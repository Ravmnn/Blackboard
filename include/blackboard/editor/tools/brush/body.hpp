#pragma once

#include <blackboard/animation/spring.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/trail.hpp>




class Brush;


class BrushBody : public Updateable, public Drawable
{
private:
    Trail trail_;


    Vector2 position_;
    Spring<float> thickness_;
    Spring<float> stretch_;

    static constexpr float IdleThicknessVariation = 2;
    static constexpr float StretchSpeedFactor = 1.0 / 3.0;

    ExponentialInterpolation<Color> color_interpolation_;


    float last_rotation_ = 0;


public:
    Brush& brush;


    explicit BrushBody(Brush& brush) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_trail() noexcept;
    void update_thickness() noexcept;
    void update_stretch() noexcept;
    void update_color() noexcept;


    void draw_body() noexcept;
    void draw_rotated_stretched_ellipse(const Vector2& position, const float radius, const float stretch, const float rotation) noexcept;
};