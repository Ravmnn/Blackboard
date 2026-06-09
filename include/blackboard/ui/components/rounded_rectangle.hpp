#pragma once

#include <blackboard/ui/components/shape.hpp>

#include <raymath.h>




namespace bb::ui
{




class RoundedRectangle : public Shape
{
protected:
    animation::Spring<Vector2> size_;
    animation::ExponentialInterpolation<float> radius_;


public:
    unsigned int segments = 16;


    RoundedRectangle(Component* parent, const Vector2& position, const Vector2& size, float radius = 0,
        const Color& color = WHITE, float outline_thickness = 0, const Color& outline_color = WHITE) noexcept;


    [[nodiscard]] const Vector2& size() const noexcept { return size_.current; }
    [[nodiscard]] Vector2 half_size() const noexcept { return size() / 2; }
    [[nodiscard]] float radius() const noexcept { return radius_; }

    void set_size(const Vector2& size) noexcept { size_.target = size; }
    void set_radius(const float radius) noexcept { radius_.target = radius;}


    void set_normalized_radius(const float normalized_radius) noexcept { radius_.target = get_radius_from_normalized(normalized_radius); }

    [[nodiscard]] float get_radius_from_normalized(const float normalized_radius) const noexcept { return normalized_radius * std::min(size_.current.x, size_.current.y); }
    [[nodiscard]] float get_normalized_radius(const float radius) const noexcept { return (radius * 2) / std::min(size_.current.x, size_.current.y); }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override {
        return { relative_position_.current.x - half_size().x, relative_position_.current.y - half_size().y, size_.current.x, size_.current.y };
    }


protected:
    void update_self() noexcept override;

    void draw_filled() noexcept override;
    void draw_outlined() noexcept override;
};




}