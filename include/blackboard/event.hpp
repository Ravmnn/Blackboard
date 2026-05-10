#pragma once

#include <functional>
#include <vector>

#include <blackboard/updateable.hpp>




template <typename... Args>
class Event : public Updateable
{
public:
    using FunctionType = std::function<void(Args...)>;


private:
    std::vector<FunctionType> callbacks_;
    bool triggered_last_frame_ = false;


public:
    Event() = default;


    void update() noexcept override { triggered_last_frame_ = false; }


    void subscribe(const FunctionType& callback) noexcept { callbacks_.push_back(callback); }
    void unsubscribe(const FunctionType& callback) noexcept { callbacks_.erase(std::remove(callbacks_.begin(), callbacks_.end(), callback), callbacks_.end()); }

    void clear() noexcept { callbacks_.clear(); }


    void trigger(Args... args) noexcept
    {
        triggered_last_frame_ = true;

        for (const auto& callback : callbacks_)
            callback(args...);
    }


    bool triggered() const noexcept { return triggered_last_frame_; }
};