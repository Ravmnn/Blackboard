#include <blackboard/ui/context.hpp>

#include <blackboard/ui/clickable.hpp>




using bb::ui::Context;




void Context::update() noexcept
{
    component_with_mouse_input_ = nullptr;

    if (!components_.empty())
        for (int i = (int)components_.size() - 1; i >= 0; i--)
            update_component_children_first(*components_[i]);
}


void Context::update_component_children_first(Component& component) noexcept
{
    if (!component.children.empty())
        for (int i = (int)component.children.size() - 1; i >= 0; i--)
            update_component_children_first(*component.children[i]);

    update_mouse_input(component);
    component.update();
}


void Context::update_mouse_input(Component& component) noexcept
{
    auto* const clickable = dynamic_cast<Clickable*>(&component);

    const bool had_component_with_mouse_input = component_with_mouse_input_;
    component_with_mouse_input_ = nullptr;

    if (!clickable)
        return;

    clickable->caught_mouse_input = false;

    if (!had_component_with_mouse_input && clickable->can_receive_input() && clickable->is_mouse_over())
    {
        clickable->caught_mouse_input = true;
        component_with_mouse_input_ = &component;
    }
}




void Context::draw() noexcept
{
    for (std::unique_ptr<Component>& component : components_)
        draw_component_parent_first(*component);
}


void Context::draw_component_parent_first(Component& component) noexcept
{
    component.draw();

    if (component.visible)
        for (std::unique_ptr<Component>& child : component.children)
            draw_component_parent_first(*child);
}