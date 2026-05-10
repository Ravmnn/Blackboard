#include <blackboard/editor/mouse_button_event.hpp>

#include <raylib.h>




void MouseButtonEvent::update() noexcept
{
    on_press.update();
    on_release.update();
    on_down.update();

    if (IsMouseButtonPressed(button_id)) on_press.trigger();
    if (IsMouseButtonReleased(button_id)) on_release.trigger();
    if (IsMouseButtonDown(button_id)) on_down.trigger();
}