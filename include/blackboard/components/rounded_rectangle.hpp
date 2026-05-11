#pragma once

#include <blackboard/components/shape.hpp>




class RoundedRectangle : public Shape
{
private:
    Spring<Vector2> size_spring_;


public:
    unsigned int segments = 32;

    float radius;
    Color color;


    RoundedRectangle(const Vector2& position, const Vector2& size, float radius, Color color) noexcept;


    void update() noexcept override;


    const Vector2& size() const noexcept { return size_spring_.current; }

    void set_size(const Vector2& size) noexcept { size_spring_.target = size; }


    void set_normalized_radius(const float normalized_radius) noexcept { radius = get_radius_from_normalized(normalized_radius); }

    float get_radius_from_normalized(const float normalized_radius) const noexcept { return normalized_radius * std::min(size_spring_.current.x, size_spring_.current.y); }
    float get_normalized_radius(const float radius) const noexcept { return radius / std::min(size_spring_.current.x, size_spring_.current.y); }


protected:
    void draw_filled() noexcept override;
    void draw_outlined() noexcept override;
};