#pragma once

#include <string>
#include <memory>
#include <optional>
#include <algorithm>

#include <blackboard/average.hpp>
#include <blackboard/stopwatch.hpp>




namespace bb::debug
{




class ProfilerItem
{
private:
    std::string id_;
    Stopwatch stopwatch_;

    std::optional<long> captured_time_ = std::nullopt;
    Average average_time_;
    long min_time_ = 0;
    long max_time_ = 0;


public:
    std::vector<std::unique_ptr<ProfilerItem>> items;


    explicit ProfilerItem(const std::string& id) noexcept;


    void capture_time() noexcept;


    void reset() noexcept { stopwatch_.reset(); }


    [[nodiscard]] bool has_item(const std::string& id) const noexcept { return get_item_with_id(id); }


    [[nodiscard]] ProfilerItem* get_item_with_id(const std::string& id) const noexcept;


    [[nodiscard]] long time_in_ms() const noexcept { return stopwatch_.elapsed_ms().count(); }

    [[nodiscard]] const std::string& id() const noexcept { return id_; }
    [[nodiscard]] long captured_time() const noexcept { return captured_time_ ? *captured_time_ : time_in_ms(); }
    [[nodiscard]] float average_time() const noexcept { return average_time_.get(); }
    [[nodiscard]] long min_time() const noexcept { return min_time_; }
    [[nodiscard]] long max_time() const noexcept { return max_time_; }
};




}