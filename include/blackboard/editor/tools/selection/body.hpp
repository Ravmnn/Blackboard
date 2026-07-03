#pragma once

#include "blackboard/animation/interpolation.hpp"
#include "blackboard/animation/spring.hpp"
#include <raylib.h>

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>




namespace bb::editor
{




class Selection;


class SelectionBody : public Updateable, public Drawable
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


private:
    void set_rectangle_to_selection_two_points() noexcept;
    void set_rectangle_idle() noexcept;

    void update_animations() noexcept;


    void on_editor_environment_changed() noexcept;
};




}