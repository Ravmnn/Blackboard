#pragma once

#include <blackboard/ui/components/component.hpp>




class RadialLayout : public Component
{
protected:
    Interpolation<float> radius_;


public:
    RadialLayout(Component* const parent, const Vector2& position, const float radius) noexcept;


    Rectangle relative_bounding_box() const noexcept override {
        return { relative_position_.current.x, relative_position_.current.y, radius_ * 2, radius_ * 2 };
    }


    float radius() const noexcept { return radius_; }

    void set_radius(const float radius) noexcept { radius_.target = radius; }


protected:
    void update_self() noexcept override;
    void update_children_position() noexcept;

    void draw_self() noexcept override {}


    virtual Vector2 get_position_for_child(Component& child, const size_t i) noexcept;
};