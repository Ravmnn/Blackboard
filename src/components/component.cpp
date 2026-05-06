#include <blackboard/components/component.hpp>




Component::Component(const Vector2& position) noexcept
    : position_spring_(position, position, DefaultSpringDamping, DefaultSpringSpeed)
{}




void Component::update() noexcept
{
    position_spring_.update();
}