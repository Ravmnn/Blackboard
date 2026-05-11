#pragma once

#include <blackboard/components/component.hpp>




class RoundedRectangle : public Component
{
private:
    Spring<Vector2> size_spring_;


public:
    unsigned int segments = 32;

    float radius;
    Color color;


    RoundedRectangle(const Vector2& position, const Vector2& size, float radius, Color color) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    const Vector2& size() const noexcept { return size_spring_.current; }

    void set_size(const Vector2& size) noexcept { size_spring_.target = size; }


private:
    float get_normalized_radius() const noexcept { return radius / std::min(size_spring_.current.x, size_spring_.current.y); }
};