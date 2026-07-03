#pragma once

#include <blackboard/ui/components/component.hpp>




namespace bb::editor
{




class RadialLayout : public ui::Component
{
protected:
    animation::ExponentialInterpolation<float> radius_;


public:
    RadialLayout(Component* parent, const Vector2& position, float radius) noexcept;


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override {
        return { relative_position.current.x, relative_position.current.y, radius_ * 2, radius_ * 2 };
    }


    [[nodiscard]] float radius() const noexcept { return radius_; }

    void set_radius(const float radius) noexcept { radius_.target = radius; }


protected:
    void update_self() noexcept override;
    void update_children_position() noexcept;

    void draw_self() noexcept override {}


    virtual Vector2 get_position_for_child(Component& child, size_t i) noexcept;
};




}