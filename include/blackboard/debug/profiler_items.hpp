#pragma once

#include <string>
#include <memory>
#include <optional>

#include <blackboard/stopwatch.hpp>




namespace bb::debug
{




class ProfilerItem
{
private:
    std::string id_;
    std::optional<long> captured_time_ = std::nullopt;


public:
    explicit ProfilerItem(const std::string& id) noexcept : id_(id) {}
    virtual ~ProfilerItem() = default;


    void capture_time() noexcept {
        if (!captured_time_)
            captured_time_ = time_in_ms();
    }


    [[nodiscard]] virtual long time_in_ms() const noexcept = 0;
    [[nodiscard]] long captured_time() const noexcept { return captured_time_ ? *captured_time_ : -1; }
};




class ProfilerStopwatchItem : public ProfilerItem
{
private:
    Stopwatch stopwatch_;


public:
    using ProfilerItem::ProfilerItem;


    void reset() noexcept { stopwatch_.reset(); }


    [[nodiscard]] long time_in_ms() const noexcept override { return stopwatch_.elapsed_ms().count(); }
};




class ProfilerGroupItem : public ProfilerItem
{
public:
    using ProfilerItem::ProfilerItem;


    std::vector<std::unique_ptr<ProfilerItem>> items;


    [[nodiscard]] long time_in_ms() const noexcept override
    {
        long accumulation = 0;

        for (const std::unique_ptr<ProfilerItem>& item : items)
            accumulation += item->time_in_ms();

        return accumulation;
    }
};




}