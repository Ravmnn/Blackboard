#pragma once

#include <memory>

#include <blackboard/drawable.hpp>
#include <blackboard/bounds.hpp>
#include <blackboard/activatable.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/animation/spring.hpp>




namespace bb::ui
{




class Component;
class Context;


template <typename T>
concept ComponentDerived = std::derived_from<T, Component>;


class Component : public Updateable, public Drawable, public Activatable, public Bounds
{
public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;
    static constexpr float DefaultInterpolationSpeed = 5;


    Component* parent = nullptr;
    std::vector<std::unique_ptr<Component>> children;

    ui::Context* ui_context = nullptr;

    bool visible = true;
    bool clip = true;


    animation::Spring<Vector2> relative_position;


    explicit Component(Component* parent, const Vector2& relative_position) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 absolute_position() const noexcept { return parent ? parent->absolute_position() + relative_position : (Vector2)relative_position; }

    [[nodiscard]] Vector2 top_left_relative_position() const noexcept { return relative_position - box_size() / 2; }
    [[nodiscard]] Vector2 top_left_absolute_position() const noexcept { return absolute_position() - box_size() / 2; }

    void set_absolute_position(const Vector2& position) noexcept { relative_position.target = position - (parent ? parent->absolute_position() : Vector2{}); }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept { return bounding_box(); }
    [[nodiscard]] Rectangle absolute_bounding_box() const noexcept;


    template <typename T>
    T* as() noexcept { return dynamic_cast<T*>(this); }


    bool is_child_of(Component& parent) const noexcept;


protected:
    virtual void begin_drawing() noexcept;
    virtual void end_drawing() noexcept;


    virtual void update_self() noexcept;
    virtual void draw_self() noexcept = 0;


    template <typename T> requires ComponentDerived<T>
    void for_each_children(const std::function<void (T*)>& function)
    {
        for (auto& child : children)
            if (auto casted = dynamic_cast<T*>(child.get()))
                function(casted);
    }


    template <typename T>
    static animation::Spring<T> create_default_spring(const T& current) noexcept
    {
        return animation::Spring<T>(current, DefaultSpringDamping, DefaultSpringSpeed);
    }


    template <typename T>
    static animation::ExponentialInterpolation<T> create_default_exponential_interpolation(const T& current) noexcept
    {
        return animation::ExponentialInterpolation<T>(current, DefaultInterpolationSpeed);
    }
};




}