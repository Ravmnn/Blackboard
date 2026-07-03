#include <blackboard/ui/components/component.hpp>

#include <blackboard/ui/context.hpp>
#include <blackboard/ui/components/component_stencil.hpp>




using bb::ui::Component;




Component::Component(Component* const parent, const Vector2& relative_position) noexcept :
    parent(parent),
    relative_position(relative_position, DefaultSpringDamping, DefaultSpringSpeed)
{
    enable();

    if (!parent)
        return;

    parent->children.emplace_back(std::unique_ptr<Component>(this));
    ui_context = parent->ui_context;
}




void Component::update() noexcept
{
    if (!active())
        return;

    update_self();
}




void Component::draw() noexcept
{
    if (!visible)
        return;

    begin_drawing();
    draw_self();
    end_drawing();
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
    relative_position.update();
}




Vector2 Component::bounding_box_size() const noexcept
{
    const Rectangle bounding_box = relative_bounding_box();
    return { bounding_box.width, bounding_box.height };
}




bool Component::is_child_of(Component& parent) const noexcept
{
    Component* current_parent = &parent;

    do
    {
        if (current_parent == this->parent)
            return true;

        current_parent = current_parent->parent;
    }
    while (current_parent);

    return false;
}