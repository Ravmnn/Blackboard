#pragma once

#include <blackboard/event.hpp>




namespace bb
{




class Activatable
{
private:
    bool active_ = false;


public:
    Event<> enabled;
    Event<> disabled;


    virtual ~Activatable() = default;


    virtual void enable() { active_ = true; enabled.trigger(); }
    virtual void disable() { active_ = false; disabled.trigger(); }

    void set_active(const bool active) noexcept { active ? enable() : disable(); }

    [[nodiscard]] bool active() const noexcept { return active_; }
};




}