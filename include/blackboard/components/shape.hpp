#pragma once

#include <blackboard/components/component.hpp>




class Shape : public Component
{
public:
    float border_thickness;
    Color border_color;


    Shape(const Vector2& position, const float border_thickness = 0, const Color& border_color = WHITE) noexcept;


    void draw() noexcept override;


protected:
    virtual void draw_filled() noexcept = 0;
    virtual void draw_outlined() noexcept = 0;
};