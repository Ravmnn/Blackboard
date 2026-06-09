#pragma once

#include <blackboard/animation/spring.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/trail.hpp>




namespace bb::editor
{




class Brush;


class BrushBody : public Updateable, public Drawable
{
private:
    Trail trail_;


    Vector2 position_;
    animation::Spring<float> thickness_;
    animation::Spring<float> stretch_;

    static constexpr float IdleThicknessVariation = 2;
    static constexpr float StretchSpeedFactor = 1.0 / 3.0;

    animation::ExponentialInterpolation<Color> color_interpolation_;


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
    void draw_rotated_stretched_ellipse(const Vector2& position, float radius, float stretch, float rotation) noexcept;
};




}