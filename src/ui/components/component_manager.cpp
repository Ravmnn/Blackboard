#include <blackboard/ui/components/component_manager.hpp>

#include <blackboard/rendering/renderer.hpp>




void ComponentManager::update() noexcept
{
    for (auto& component : components)
        component->update();
}




void ComponentManager::draw() noexcept
{
    for (auto& component : components)
        component->draw();
}