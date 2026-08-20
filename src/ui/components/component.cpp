#include <blackboard/ui/components/component.hpp>

#include <blackboard/ui/components/component_stencil.hpp>




using
bb::rendering::Stencil,
bb::ui::Component;




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

    begin_stencil();
    draw_self();
    end_stencil();
}




void Component::begin_stencil() noexcept
{
    if (!clip)
        return;

    Stencil::enable();
    Stencil::begin_write(GL_EQUAL, stencil_id(), GL_INCR);
}


void Component::end_stencil() noexcept
{
    Stencil::disable();
}




void Component::update_self() noexcept
{
    relative_position.update();
}




uint8_t Component::stencil_id() const noexcept
{
    return ComponentStencil::get_stencil_id_of_component(*this);
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