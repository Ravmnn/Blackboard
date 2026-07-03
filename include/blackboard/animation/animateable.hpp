#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/vector.hpp>




namespace bb::animation
{




template <typename T>
class Animateable : public Updateable
{
public:
    T current = {}, target = {};
    bool immediate = false;


    Animateable() = default;
    explicit Animateable(const T& current) noexcept
        : current(current), target(current) {}


    Animateable<T>& operator=(const Animateable<T>&) = delete;


    operator T() const noexcept { return current; }
    T& operator=(const T& value) noexcept { return target = value; }


    virtual void set_value_immediately(const T& value) noexcept { current = target = value; }

    T& set_target_and_update(const T& target) noexcept
    {
        this->target = target;
        update();

        return current;
    }
};





}