#pragma once

#include <functional>

#include <blackboard/ui/components/component.hpp>
#include <blackboard/ui/focusable.hpp>




namespace bb::ui
{




template <typename T>
concept ComponentAndFocusable = std::derived_from<T, ui::Focusable> && std::derived_from<T, ui::Component>;


class Context : public Updateable, public Drawable
{
private:
    std::vector<std::unique_ptr<Component>> components_;

    Component* component_with_mouse_input_ = nullptr;
    Component* component_with_focus_ = nullptr;


public:
    void update() noexcept override;
    void draw() noexcept override;


    void add_component(Component& component) noexcept { components_.push_back(std::unique_ptr<Component>(&component)); }

    [[nodiscard]] const std::vector<std::unique_ptr<Component>>& components() const noexcept { return components_; }
    [[nodiscard]] Component* component_with_mouse_input() noexcept { return component_with_mouse_input_; }
    [[nodiscard]] Component* component_with_focus() noexcept { return component_with_focus_; }


    template <typename T> requires ComponentAndFocusable<T>
    void set_focus_to(T* component) noexcept;


private:
    void update_focus() noexcept;
    void update_component_children_first(Component& component) noexcept;
    void update_mouse_input(Component& component) noexcept;

    void draw_component_parent_first(Component& component) noexcept;


    void for_each_component(const std::function<void (Component&)>& operation) noexcept;
    void for_each_child_recursively(Component& component, const std::function<void (Component&)>& operation) noexcept;
};



template <typename T> requires ComponentAndFocusable<T>
void Context::set_focus_to(T* component) noexcept
{
    if (component == component_with_focus_)
        return;

    if (component)
        component->focus();

    component_with_focus_ = component;

    for_each_component([&](Component& c) {
        if (auto* focusable = c.as<Focusable>(); focusable && focusable != component)
            focusable->unfocus();
    });
}




}