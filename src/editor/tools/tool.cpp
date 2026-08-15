#include <blackboard/editor/tools/tool.hpp>

#include <blackboard/editor/editor_environment.hpp>




using
bb::editor::Tool,
bb::editor::Editor;




Tool::Tool(EditorEnvironment& environment) noexcept :
    environment(environment)
{
    got_active.subscribe([this]() { on_got_active(); }, "editor::Tool::got_active_callback");
    got_inactive.subscribe([this]() { on_got_inactive(); }, "editor::Tool::got_inactive_callback");

    changed_in.subscribe([this]() { on_changed_in(); }, "editor::Tool::changed_in_callback");
    changed_out.subscribe([this]() { on_changed_out(); }, "editor::Tool::changed_out_callback");
}




void Tool::update() noexcept
{
    update_active_state();

    if (active())
        update_when_active();
}


void Tool::update_active_state() noexcept
{
    got_active.update();
    got_inactive.update();

    if (!was_active_ && active())
        got_active.trigger();

    if (was_active_ && !active())
        got_inactive.trigger();

    was_active_ = active();
}




Editor& Tool::editor() noexcept
{
    return environment.editor;
}


const Editor& Tool::editor() const noexcept
{
    return environment.editor;
}