#include <blackboard/ui/context.hpp>

#include <blackboard/debug/profiler.hpp>
#include <blackboard/ui/clickable.hpp>




using bb::ui::Context,
    bb::debug::Profiler;




void Context::update() noexcept
{
    Profiler::begin("ui::update");


    component_with_mouse_input_ = nullptr;

    update_focus();

    if (!components_.empty())
        for (int i = (int)components_.size() - 1; i >= 0; i--)
            update_component_children_first(*components_[i]);


    Profiler::end();
}


void Context::update_focus() noexcept
{
    if (component_with_focus_)
        if (auto* focusable = component_with_focus_->as<Focusable>(); focusable && !focusable->is_focused())
            component_with_focus_ = nullptr;
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

    if (!disable_mouse_input && !had_component_with_mouse_input && clickable->can_receive_input() && clickable->is_mouse_over())
    {
        clickable->caught_mouse_input = true;
        component_with_mouse_input_ = &component;
    }
}




void Context::draw() noexcept
{
    Profiler::begin("ui::draw");


    for (std::unique_ptr<Component>& component : components_)
        draw_component_parent_first(*component);


    Profiler::end();
}


void Context::draw_component_parent_first(Component& component) noexcept
{
    component.draw();

    if (component.visible)
        for (std::unique_ptr<Component>& child : component.children)
            draw_component_parent_first(*child);
}




void Context::for_each_component(const std::function<void (Component&)>& operation) noexcept
{
    for (auto& component : components_)
    {
        operation(*component);
        for_each_child_recursively(*component, operation);
    }
}


void Context::for_each_child_recursively(Component& component, const std::function<void (Component&)>& operation) noexcept
{
    for (auto& child : component.children)
    {
        operation(*child);
        for_each_child_recursively(*child, operation);
    }
}