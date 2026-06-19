#include <blackboard/editor/tools/tool.hpp>




using bb::editor::Tool;




void Tool::update() noexcept
{
    update_active_state();
}


void Tool::update_active_state() noexcept
{
    got_inactive_ = false;
    got_active_ = false;

    if (!was_active_ && active())
        got_active_ = true;

    if (was_active_ && !active())
        got_inactive_ = true;

    was_active_ = active();
}