#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerItem;




ProfilerItem::ProfilerItem(const std::string& id) noexcept
    : id_(id), average_time_ns_(128)
{}




void ProfilerItem::capture_time() noexcept
{
    const long time = time_in_ns();

    if (!captured_time_ns_)
        min_time_ns_ = max_time_ns_= time;

    captured_time_ns_ = time;
    average_time_ns_.add((float)time);

    if (time > max_time_ns_)
        max_time_ns_ = time;

    if (time < min_time_ns_)
        min_time_ns_ = time;
}




ProfilerItem* ProfilerItem::get_item_with_id(const std::string& id) const noexcept
{
    auto item = std::find_if(items.cbegin(), items.cend(), [&](const auto& item) { return item->id() == id; });

    return item == items.cend() ? nullptr : item->get();
}