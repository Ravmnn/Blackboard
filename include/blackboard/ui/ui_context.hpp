#pragma once

#include <blackboard/ui/components/component.hpp>



class UIContext : public Updateable, public Drawable
{
private:
    std::vector<std::unique_ptr<Component>> components_;

    Component* component_with_mouse_input_ = nullptr;


public:
    void update() noexcept override;
    void draw() noexcept override;


    void add_component(Component& component) noexcept { components_.push_back(std::unique_ptr<Component>(&component)); }

    const std::vector<std::unique_ptr<Component>>& components() const noexcept { return components_; }
    Component* component_with_mouse_input() noexcept { return component_with_mouse_input_; }


private:
    void update_component_children_first(Component& component) noexcept;
    void update_mouse_input(Component& component) noexcept;

    void draw_component_parent_first(Component& component) noexcept;
};