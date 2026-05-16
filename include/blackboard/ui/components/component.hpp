#pragma once

#include <memory>
#include <vector>

#include <raylib.h>
#include <raymath.h>

#include <blackboard/animation/spring.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/vector.hpp>




class Component : public virtual Updateable, public Drawable
{
protected:
    Spring<Vector2> relative_position_;


public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;
    static constexpr float DefaultInterpolationSpeed = 5;


    Component* parent = nullptr;
    std::vector<std::unique_ptr<Component>> children;

    bool clip = true;


    explicit Component(Component* const parent, const Vector2& relative_position) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    Vector2 relative_position() const noexcept { return relative_position_.current - bounding_box_size() / 2; }
    Vector2 absolute_position() const noexcept { return parent ? parent->absolute_position() + relative_position_ : relative_position(); }

    void set_relative_position(const Vector2& position) noexcept { relative_position_.target = position; }
    void set_absolute_position(const Vector2& position) noexcept { relative_position_.target = position - (parent ? parent->absolute_position() : Vector2{}); }


    virtual Rectangle relative_bounding_box() const noexcept = 0;
    virtual Rectangle absolute_bounding_box() const noexcept;

    Vector2 bounding_box_size() const noexcept;


protected:
    Vector2 render_position() const noexcept { return absolute_position() - bounding_box_size() / 2; }


    virtual void begin_drawing() noexcept;
    virtual void end_drawing() noexcept;


    virtual void update_self() noexcept;
    virtual void draw_self() noexcept = 0;


    template <typename T>
    static Spring<T> create_default_spring(const T& current) noexcept
    {
        return Spring<T>(current, current, DefaultSpringDamping, DefaultSpringSpeed);
    }


    template <typename T>
    static Interpolation<T> create_default_interpolation(const T& current) noexcept
    {
        return Interpolation<T>(current, DefaultInterpolationSpeed);
    }
};