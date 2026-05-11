#pragma once

#include <blackboard/components/component.hpp>




class Shape : public Component
{
public:
    Color color;

    float border_thickness;
    Color border_color;


    Shape(Component* const parent, const Vector2& relative_position, const Color& color = WHITE, const float border_thickness = 0,
        const Color& border_color = WHITE) noexcept;


    void draw() noexcept override;


protected:
    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};