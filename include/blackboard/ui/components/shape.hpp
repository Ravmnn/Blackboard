#pragma once

#include <blackboard/ui/components/component.hpp>
#include <blackboard/animation/interpolation.hpp>




class Shape : public Component
{
protected:
    Interpolation<Color> color_;
    Interpolation<float> outline_thickness_;
    Interpolation<Color> outline_color_;


public:
    Shape(Component* const parent, const Vector2& relative_position, const Color& color = WHITE, const float outline_thickness = 0,
        const Color& outline_color = WHITE) noexcept;


    const Color& color() const noexcept { return color_; }
    float outline_thickness() const noexcept { return outline_thickness_; }
    const Color& outline_color() const noexcept { return outline_color_; }

    void set_color(const Color& color) noexcept { color_.target = color; }
    void set_outline_thickness(const float thickness) noexcept { outline_thickness_.target = thickness; }
    void set_outline_color(const Color& outline_color) noexcept { outline_color_.target = outline_color; }


protected:
    void update_self() noexcept override;

    void draw_self() noexcept override;
    void draw_outline() noexcept;

    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};