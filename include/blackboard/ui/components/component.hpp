#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <concepts>

#include <blackboard/animation/spring.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/vector.hpp>
#include <blackboard/activatable.hpp>




namespace bb::ui
{




class Component;
class Context;


template <typename T>
concept ComponentDerived = std::derived_from<T, Component>;


class Component : public virtual Updateable, public Drawable, public Activatable
{
protected:
    animation::Spring<Vector2> relative_position_;


public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;
    static constexpr float DefaultInterpolationSpeed = 5;


    Component* parent = nullptr;
    std::vector<std::unique_ptr<Component>> children;

    ui::Context* ui_context = nullptr;

    bool visible = true;
    bool clip = true;


    explicit Component(Component* parent, const Vector2& relative_position) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 relative_position() const noexcept { return relative_position_.current; }
    [[nodiscard]] Vector2 absolute_position() const noexcept { return parent ? parent->absolute_position() + relative_position_ : relative_position_; }

    [[nodiscard]] Vector2 top_left_relative_position() const noexcept { return relative_position() - bounding_box_size() / 2; }
    [[nodiscard]] Vector2 top_left_absolute_position() const noexcept { return absolute_position() - bounding_box_size() / 2; }

    void set_relative_position(const Vector2& position) noexcept { relative_position_.target = position; }
    void set_absolute_position(const Vector2& position) noexcept { relative_position_.target = position - (parent ? parent->absolute_position() : Vector2{}); }


    [[nodiscard]] virtual Rectangle relative_bounding_box() const noexcept = 0;
    [[nodiscard]] virtual Rectangle absolute_bounding_box() const noexcept {
        return { top_left_absolute_position().x, top_left_absolute_position().y, bounding_box_size().x, bounding_box_size().y };
    }

    [[nodiscard]] Vector2 bounding_box_size() const noexcept;


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
        return animation::Spring<T>(current, current, DefaultSpringDamping, DefaultSpringSpeed);
    }


    template <typename T>
    static animation::ExponentialInterpolation<T> create_default_exponential_interpolation(const T& current) noexcept
    {
        return animation::ExponentialInterpolation<T>(current, DefaultInterpolationSpeed);
    }
};




}