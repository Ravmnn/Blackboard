#include <blackboard/debug/profiler.hpp>

#include <cassert>




using bb::debug::Profiler,
    bb::debug::ProfilerItem;




void Profiler::begin(const std::string& id) noexcept
{
    if (disable)
        return;

    if (!current_item()->has_item(id))
        current_item()->items.push_back(std::make_unique<ProfilerItem>(id));

    items_.push(current_item()->get_item_with_id(id));
    current_item()->reset();
}


void Profiler::end() noexcept
{
    if (disable)
        return;

    current_item()->capture_time();
    items_.pop();
}




ProfilerItem* Profiler::current_item() noexcept
{
    if (!items_.empty())
        return items_.top();

    return root_.get();
}