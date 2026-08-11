#pragma once

#include <string>
#include <memory>
#include <optional>

#include <blackboard/average.hpp>
#include <blackboard/stopwatch.hpp>




namespace bb::debug
{




class ProfilerItem
{
private:
    std::string id_;
    Stopwatch stopwatch_;

    std::optional<long> captured_time_ns_ = std::nullopt;
    Average average_time_ns_;
    long min_time_ns_ = 0;
    long max_time_ns_ = 0;


public:
    std::vector<std::unique_ptr<ProfilerItem>> items;


    explicit ProfilerItem(const std::string& id) noexcept;


    void capture_time() noexcept;


    void reset() noexcept { stopwatch_.reset(); }


    [[nodiscard]] bool has_item(const std::string& id) const noexcept { return get_item_with_id(id); }


    [[nodiscard]] ProfilerItem* get_item_with_id(const std::string& id) const noexcept;


    [[nodiscard]] long time_in_ns() const noexcept { return stopwatch_.elapsed_ns().count(); }

    [[nodiscard]] const std::string& id() const noexcept { return id_; }
    [[nodiscard]] long captured_time_ns() const noexcept { return captured_time_ns_ ? *captured_time_ns_ : time_in_ns(); }
    [[nodiscard]] long average_time_ns() const noexcept { return (long)average_time_ns_.get(); }
    [[nodiscard]] long min_time_ns() const noexcept { return min_time_ns_; }
    [[nodiscard]] long max_time_ns() const noexcept { return max_time_ns_; }
};




}