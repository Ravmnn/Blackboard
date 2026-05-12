#pragma once

#include <blackboard/components/component.hpp>




class Shape : public Component
{
public:
    Color color;

    float outline_thickness;
    Color outline_color;


    Shape(Component* const parent, const Vector2& relative_position, const Color& color = WHITE, const float outline_thickness = 0,
        const Color& outline_color = WHITE) noexcept;


protected:
    void draw_self() noexcept override;
    void draw_outline() noexcept;

    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};