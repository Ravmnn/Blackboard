#pragma once

#include <blackboard/components/shape.hpp>

#include <raymath.h>




class RoundedRectangle : public Shape
{
protected:
    Spring<Vector2> size_;
    Interpolation<float> radius_;


public:
    unsigned int segments = 16;


    RoundedRectangle(Component* const parent, const Vector2& position, const Vector2& size, const float radius = 0,
        const Color& color = WHITE, const float outline_thickness = 0, const Color& outline_color = WHITE) noexcept;


    const Vector2& size() const noexcept { return size_.current; }
    float radius() const noexcept { return radius_; }

    void set_size(const Vector2& size) noexcept { size_.target = size; }
    void set_radius(const float radius) noexcept { radius_.target = radius;}


    void set_normalized_radius(const float normalized_radius) noexcept { radius_.target = get_radius_from_normalized(normalized_radius); }

    float get_radius_from_normalized(const float normalized_radius) const noexcept { return normalized_radius * std::min(size_.current.x, size_.current.y); }
    float get_normalized_radius(const float radius) const noexcept { return radius / std::min(size_.current.x, size_.current.y); }


protected:
    void update_self() noexcept override;

    void draw_filled() noexcept override;
    void draw_outlined() noexcept override;
};