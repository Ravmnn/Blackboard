#include <blackboard/editor/tools/tool.hpp>

#include <blackboard/editor/editor_environment.hpp>




using bb::editor::Tool,
    bb::editor::Editor;




Tool::Tool(EditorEnvironment& environment) noexcept :
    environment(environment)
{
    changed_in.subscribe([this]() { on_changed_in(); }, "editor::Tool::changed_in_callback");
    changed_out.subscribe([this]() { on_changed_out(); }, "editor::Tool::changed_out_callback");
}




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




Editor& Tool::editor() noexcept
{
    return environment.editor;
}


const Editor& Tool::editor() const noexcept
{
    return environment.editor;
}