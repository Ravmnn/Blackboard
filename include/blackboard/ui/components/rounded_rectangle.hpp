#pragma once

#include <blackboard/math/rect.hpp>
#include <blackboard/ui/components/shape.hpp>

#include <raymath.h>




namespace bb::ui
{




class RoundedRectangle : public Shape
{
public:
    animation::Spring<Vector2> size;
    animation::ExponentialInterpolation<float> radius;

    unsigned int resolution = 32;


    RoundedRectangle(Component* parent, const Vector2& position, const Vector2& size, float radius = 0,
        const Color& color = WHITE, float outline_thickness = 0, const Color& outline_color = WHITE) noexcept;


    [[nodiscard]] Vector2 half_size() const noexcept { return size / 2; }


    void set_normalized_radius(const float normalized_radius) noexcept {
        radius.target = math::Rect::get_corner_radius_from_normalized(size, normalized_radius);
    }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override {
        return { relative_position.current.x - half_size().x, relative_position.current.y - half_size().y, size.current.x, size.current.y };
    }


protected:
    void update_self() noexcept override;

    void draw_filled() noexcept override;
    void draw_outlined() noexcept override;
};




}