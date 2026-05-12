#pragma once

#include <memory>
#include <vector>

#include <raylib.h>
#include <raymath.h>

#include <blackboard/animation/spring.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/vector.hpp>




class Component : public Updateable, public Drawable
{
protected:
    Spring<Vector2> relative_position_;


public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;


    Component* parent = nullptr;
    std::vector<std::unique_ptr<Component>> children;


    explicit Component(Component* const parent, const Vector2& relative_position) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    const Vector2& relative_position() const noexcept { return relative_position_.current; }
    Vector2 absolute_position() const noexcept { return parent ? parent->absolute_position() + relative_position_.current : relative_position_.current; }

    void set_relative_position(const Vector2& position) noexcept { relative_position_.target = position; }
    void set_absolute_position(const Vector2& position) noexcept { relative_position_.target = position - (parent ? parent->absolute_position() : Vector2{}); }


protected:
    virtual void begin_drawing() noexcept;
    virtual void end_drawing() noexcept;


    virtual void update_self() noexcept;
    virtual void draw_self() noexcept = 0;

    void decrement_geometry_stencil() noexcept;


    template <typename T>
    static Spring<T> create_default_spring(const T& current) noexcept
    {
        return Spring<T>(current, current, DefaultSpringDamping, DefaultSpringSpeed);
    }
};