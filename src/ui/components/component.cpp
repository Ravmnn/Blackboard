#include <blackboard/ui/components/component.hpp>

#include <blackboard/ui/components/component_stencil.hpp>




Component::Component(Component* const parent, const Vector2& relative_position) noexcept :
    relative_position_(relative_position, relative_position, DefaultSpringDamping, DefaultSpringSpeed),
    parent(parent)
{
    enable();

    if (parent)
        parent->children.emplace_back(std::unique_ptr<Component>(this));
}




void Component::update() noexcept
{
    if (!active())
        return;

    update_self();

    for (const auto& child : children)
        child->update();
}




void Component::draw() noexcept
{
    if (!visible)
        return;

    begin_drawing();
    draw_self();
    end_drawing();

    for (const auto& child : children)
        child->draw();
}




void Component::begin_drawing() noexcept
{
    if (!clip)
        return;

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




Vector2 Component::bounding_box_size() const noexcept
{
    const Rectangle bounding_box = relative_bounding_box();
    return { bounding_box.width, bounding_box.height };
}