#include <blackboard/components/component.hpp>




Component::Component(Component* const parent, const Vector2& relative_position) noexcept
    : parent(parent), relative_position_(relative_position, relative_position, DefaultSpringDamping, DefaultSpringSpeed)
{
    if (parent)
        parent->children.emplace_back(std::unique_ptr<Component>(this));
}




void Component::update() noexcept
{
    relative_position_.update();

    for (const auto& child : children)
        child->update();
}




void Component::draw() noexcept
{
    for (const auto& child : children)
        child->draw();
}