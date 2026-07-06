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




Rectangle Component::absolute_bounding_box() const noexcept
{
    const Vector2 absolute_position = top_left_absolute_position();
    const Vector2 size = box_size();

    return { absolute_position.x, absolute_position.y, size.x, size.y };
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