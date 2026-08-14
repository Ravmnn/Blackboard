#include <blackboard/ui/context.hpp>

#include <blackboard/debug/profiler.hpp>
#include <blackboard/ui/clickable.hpp>




using
bb::debug::Profiler,
bb::ui::Context;




void Context::update() noexcept
{
    Profiler::begin("ui::update");


    components_with_mouse_input_.clear();

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

    if (!clickable)
        return;

    const bool has_any_component_with_mouse_input = !components_with_mouse_input_.empty();
    const bool last_component_with_mouse_input_blocks_input = has_any_component_with_mouse_input && components_with_mouse_input_.front()->as<Clickable>()->block_input;

    const bool should_get_input = clickable->can_receive_input() && clickable->is_mouse_over();
    const bool should_block_input = has_any_component_with_mouse_input && last_component_with_mouse_input_blocks_input;

    clickable->caught_mouse_input = false;

    if (!disable_mouse_input && !should_block_input && should_get_input)
    {
        clickable->caught_mouse_input = true;
        components_with_mouse_input_.push_back(&component);
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