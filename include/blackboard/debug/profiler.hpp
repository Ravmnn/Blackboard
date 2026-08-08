#pragma once

#include <stack>

#include <blackboard/debug/profiler_items.hpp>




namespace bb::debug
{




class Profiler
{
private:
    inline static std::unique_ptr<ProfilerGroupItem> root_group_ = std::make_unique<ProfilerGroupItem>("total");

    static std::stack<ProfilerGroupItem*> groups_;
    inline static ProfilerStopwatchItem* current_stopwatch_ = nullptr;


public:
    static void begin_group(const std::string& id) noexcept;
    static void end_group() noexcept;

    static void begin_item(const std::string& id) noexcept;
    static void end_item() noexcept;

    static void reset() noexcept;


    static ProfilerGroupItem* current_group() noexcept;
    static const ProfilerGroupItem* root() noexcept { return root_group_.get(); }
};




}