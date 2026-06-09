#pragma once

#include <blackboard/ui/components/component.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::ui
{




class Shape : public Component
{
protected:
    animation::ExponentialInterpolation<Color> color_;
    animation::ExponentialInterpolation<float> outline_thickness_;
    animation::ExponentialInterpolation<Color> outline_color_;


public:
    Shape(Component* parent, const Vector2& relative_position, const Color& color = WHITE, float outline_thickness = 0,
        const Color& outline_color = WHITE) noexcept;


    [[nodiscard]] const Color& color() const noexcept { return color_.current; }
    [[nodiscard]] float outline_thickness() const noexcept { return outline_thickness_; }
    [[nodiscard]] const Color& outline_color() const noexcept { return outline_color_.current; }
    [[nodiscard]] uint8_t opacity() const noexcept { return color_.current.a; }
    [[nodiscard]] uint8_t outline_opacity() const noexcept { return outline_color_.current.a; }

    void set_color(const Color& color) noexcept { color_.target = color; }
    void set_outline_thickness(const float thickness) noexcept { outline_thickness_.target = thickness; }
    void set_outline_color(const Color& outline_color) noexcept { outline_color_.target = outline_color; }
    void set_opacity(const uint8_t opacity) noexcept { color_.target.a = opacity; }
    void set_outline_opacity(const uint8_t opacity) noexcept { outline_color_.target.a = opacity; }
    void set_both_color(const Color& color) noexcept { color_.target = outline_color_.target = color; }
    void set_both_opacity(const uint8_t opacity) noexcept { color_.target.a = outline_color_.target.a = opacity; }


protected:
    void update_self() noexcept override;

    void draw_self() noexcept override;
    void draw_outline() noexcept;

    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};




}