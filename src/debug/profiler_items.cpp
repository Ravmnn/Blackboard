#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerItem;




ProfilerItem::ProfilerItem(const std::string& id) noexcept
    : id_(id), average_time_(256)
{}




void ProfilerItem::capture_time() noexcept
{
    const long time = time_in_ms();

    if (!captured_time_)
        min_time_ = max_time_= time;

    captured_time_ = time;
    average_time_.add((float)time);

    if (time > max_time_)
        max_time_ = time;

    if (time < min_time_)
        min_time_ = time;
}




ProfilerItem* ProfilerItem::get_item_with_id(const std::string& id) const noexcept
{
    auto item = std::find_if(items.cbegin(), items.cend(), [&](const auto& item) { return item->id() == id; });

    return item == items.cend() ? nullptr : item->get();
}