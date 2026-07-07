#include <blackboard/ui/components/component_manager.hpp>




using bb::ui::ComponentManager;




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