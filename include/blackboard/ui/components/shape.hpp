#pragma once

#include <blackboard/ui/components/component.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::ui
{




class Shape : public Component
{
public:
    animation::ExponentialInterpolation<Color> color;
    animation::ExponentialInterpolation<float> outline_thickness;
    animation::ExponentialInterpolation<Color> outline_color;


    Shape(Component* parent, const Vector2& relative_position, const Color& color = WHITE, float outline_thickness = 0,
        const Color& outline_color = WHITE) noexcept;


    void set_both_color(const Color& color) noexcept { this->color = outline_color = color; }
    void set_both_opacity(const uint8_t opacity) noexcept { color.target.a = outline_color.target.a = opacity; }


protected:
    void update_self() noexcept override;

    void draw_self() noexcept override;
    void draw_outline() noexcept;

    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};




}