#include <blackboard/ui/scrollable.hpp>




using bb::ui::Scrollable;




void Scrollable::update() noexcept
{
    Clickable::update();

    scroll_down.update();
    scroll_up.update();

    if (!caught_mouse_input)
        return;

    if (GetMouseWheelMove() > 0)
        scroll_up.trigger();

    if (GetMouseWheelMove() < 0)
        scroll_down.trigger();
}




int Scrollable::scroll_value() const noexcept
{
    if (scroll_up.triggered())
        return 1;

    if (scroll_down.triggered())
        return -1;

    return 0;
}