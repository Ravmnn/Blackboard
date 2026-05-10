#pragma once

#include <functional>
#include <vector>




template <typename... Args>
class Event
{
private:
    std::vector<FunctionType> callbacks_;


public:
    using FunctionType = std::function<void(Args...)>;


    void subscribe(const FunctionType& callback) noexcept { callbacks_.push_back(callback); }
    void unsubscribe(const FunctionType& callback) noexcept { callbacks_.erase(std::remove(callbacks_.begin(), callbacks_.end(), callback), callbacks_.end()); }

    void clear() noexcept { callbacks_.clear(); }


    void trigger(Args... args) const noexcept
    {
        for (const auto& callback : callbacks_)
            callback(args...);
    }
};