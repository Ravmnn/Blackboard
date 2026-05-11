#pragma once

#include <raylib.h>

#include <blackboard/animation/spring.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/vector.hpp>




class Component : public Updateable, public Drawable
{
protected:
    Spring<Vector2> position_spring_;


public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;


    explicit Component(const Vector2& position) noexcept;


    void update() noexcept override;


    const Vector2& position() const noexcept { return position_spring_.current; }

    void set_position(const Vector2& position) noexcept { position_spring_.target = position; }


protected:
    template <typename T>
    static Spring<T> create_default_spring(const T& current) noexcept
    {
        return Spring<T>(current, current, DefaultSpringDamping, DefaultSpringSpeed);
    }
};