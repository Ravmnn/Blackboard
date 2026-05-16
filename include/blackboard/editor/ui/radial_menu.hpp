#pragma once

#include <blackboard/ui/components/component.hpp>




class RadialMenu : public Component
{
private:
    Interpolation<float> radius_;


public:
    RadialMenu(Component* const parent, const Vector2& position, const float radius) noexcept;


    Rectangle relative_bounding_box() const noexcept override {
        return { relative_position_.current.x, relative_position_.current.y, radius_ * 2, radius_ * 2 };
    }


protected:
    void update_self() noexcept override;
    void update_children_position() noexcept;

    void draw_self() noexcept override {}
};