#include <blackboard/ui/components/component_stencil.hpp>

#include <blackboard/ui/components/component.hpp>




uint8_t ComponentStencil::get_stencil_value_for_component(const Component& component) noexcept
{
    uint8_t id = 0;
    Component* parent = component.parent;

    while (parent)
    {
        parent = parent->parent;
        id++;
    }

    return id;
}