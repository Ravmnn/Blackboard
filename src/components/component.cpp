#include <blackboard/components/component.hpp>

#include <blackboard/components/component_stencil.hpp>




Component::Component(Component* const parent, const Vector2& relative_position) noexcept
    : parent(parent), relative_position_(relative_position, relative_position, DefaultSpringDamping, DefaultSpringSpeed)
{
    if (parent)
        parent->children.emplace_back(std::unique_ptr<Component>(this));
}




void Component::update() noexcept
{
    update_self();

    for (const auto& child : children)
        child->update();
}




void Component::draw() noexcept
{
    begin_drawing();
    draw_self();
    end_drawing();

    for (const auto& child : children)
        child->draw();
}




void Component::begin_drawing() noexcept
{
    ComponentStencil::enable();
    ComponentStencil::mask_and_increment(*this);
}


void Component::end_drawing() noexcept
{
    ComponentStencil::disable();
}




void Component::update_self() noexcept
{
    relative_position_.update();
}