#pragma once

#include <cassert>

#include <functional>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>


#include <blackboard/updateable.hpp>




namespace bb
{




template <typename... Args>
struct Callback
{
    using FunctionType = std::function<void(Args...)>;


    FunctionType function;
    std::optional<std::string> id;


    Callback(const FunctionType& function, const std::optional<std::string>& id = std::nullopt) noexcept :
        function(function),
        id(id)
    {}


    bool operator==(const Callback<Args...>& other) const noexcept
    {
        if (!id || !other.id)
            return false;

        return id == other.id;
    }
};




template <typename... Args>
class Event : public Updateable
{
private:
    std::vector<Callback<Args...>> callbacks_;
    bool triggered_last_frame_ = false;


public:
    void update() noexcept override { triggered_last_frame_ = false; }


    void subscribe(const Callback<Args...>::FunctionType& function, const std::optional<std::string>& id = std::nullopt) noexcept
    {
        if (auto callback = Callback(function, id); !std::ranges::contains(callbacks_, callback))
            subscribe(callback);
    }

    void subscribe(const Callback<Args...>& callback) noexcept
    {
        if (!std::ranges::contains(callbacks_, callback))
            callbacks_.push_back(callback);
    }


    void unsubscribe(const std::string& id) noexcept
    {
        const auto predicate = [&id](const Callback<Args...>& callback) { return callback.id.has_value() ? *callback.id == id : false; };
        callbacks_.erase(std::remove_if(callbacks_.begin(), callbacks_.end(), predicate), callbacks_.end());
    }

    void unsubscribe(const Callback<Args...>::FunctionType& callback_function) noexcept
    {
        const auto predicate = [&callback_function](const Callback<Args...>& callback) { return callback.function == callback_function; };
        callbacks_.erase(std::remove_if(callbacks_.begin(), callbacks_.end(), predicate), callbacks_.end());
    }


    void clear() noexcept { callbacks_.clear(); }


    void trigger(Args... args) noexcept
    {
        triggered_last_frame_ = true;

        for (const auto& callback : callbacks_)
            callback.function(args...);
    }


    [[nodiscard]] bool triggered() const noexcept { return triggered_last_frame_; }
};




}