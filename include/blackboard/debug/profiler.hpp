#pragma once

#include <stack>

#include <blackboard/debug/profiler_items.hpp>




namespace bb::debug
{




class Profiler
{
private:
    inline static std::unique_ptr<ProfilerItem> root_ = std::make_unique<ProfilerItem>("total");

    inline static std::stack<ProfilerItem*> items_;


public:
    inline static bool disable = false;

    static void begin_root() noexcept { root_->reset(); }
    static void end_root() noexcept { root_->capture_time(); }

    static void begin(const std::string& id) noexcept;
    static void end() noexcept;

    static void reset() noexcept { items_ = {}; }
    static void clear() noexcept { root_->items.clear(); }


    static ProfilerItem* current_item() noexcept;
    static const ProfilerItem* root() noexcept { return root_.get(); }
};




}