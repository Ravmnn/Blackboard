#include <blackboard/debug/profiler.hpp>

#include <cassert>




using bb::debug::Profiler,
    bb::debug::ProfilerGroupItem;




void Profiler::begin_group(const std::string& id) noexcept
{
    auto* const group = new ProfilerGroupItem(id);
    current_group()->items.push_back(std::unique_ptr<ProfilerGroupItem>(group));
    groups_.push(group);
}


void Profiler::end_group() noexcept
{
    assert(!groups_.empty());
    groups_.pop();
}




void Profiler::begin_item(const std::string& id) noexcept
{
    assert(!current_stopwatch_);
    current_stopwatch_ = new ProfilerStopwatchItem(id);
}


void Profiler::end_item() noexcept
{
    assert(current_stopwatch_);
    current_stopwatch_->capture_time();
    current_group()->items.push_back(std::unique_ptr<ProfilerStopwatchItem>(current_stopwatch_));
}




void Profiler::reset() noexcept
{
    root_group_->items.clear();
}




ProfilerGroupItem* Profiler::current_group() noexcept
{
    if (!groups_.empty())
        return groups_.top();

    return root_group_.get();
}