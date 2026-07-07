#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/bounds.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::editor
{




class Selection;


class SelectionBody : public Updateable, public Drawable, public Bounds
{
private:
    animation::ExponentialInterpolation<Vector2> rectangle_position_;
    animation::ExponentialInterpolation<Vector2> rectangle_size_;

    Color rectangle_color_ = ColorAlpha(RED, 0.3);
    Color rectangle_outline_color_ = ColorAlpha(RED, 0.7);

    static constexpr float IdleSize = 20;
    static constexpr float Radius = 5;


public:
    Selection& selection;


    explicit SelectionBody(Selection& selection) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Rectangle bounding_box() const noexcept override {
        return { rectangle_position_.current.x, rectangle_position_.current.y, rectangle_size_.current.x, rectangle_size_.current.y };
    }


private:
    void set_rectangle_to_selection_two_points() noexcept;
    void set_rectangle_idle() noexcept;

    void update_animations() noexcept;


    void on_editor_environment_changed() noexcept;
};




}