#pragma once

#include <blackboard/event.hpp>




namespace bb
{




// TODO: go through all project and check whether a class should be copiable, movable or neither
class Activatable
{
private:
    bool active_ = false;


public:
    Event<> enabled;
    Event<> disabled;


    Activatable() noexcept
    {
        enabled.subscribe([this]() { on_enabled(); }, "bb::Activatable::enabled_event_callback");
        disabled.subscribe([this]() { on_disabled(); }, "bb::Activatable::disabled_event_callback");
    }

    virtual ~Activatable() = default;

    Activatable(const Activatable&) = delete;
    Activatable& operator=(const Activatable&) = delete;
    Activatable(Activatable&&) = delete;
    Activatable& operator=(Activatable&&) = delete;


    virtual void enable() { active_ = true; enabled.trigger(); }
    virtual void disable() { active_ = false; disabled.trigger(); }

    void set_active(const bool active) noexcept { active ? enable() : disable(); }

    [[nodiscard]] bool active() const noexcept { return active_; }


protected:
    virtual void on_enabled() {}
    virtual void on_disabled() {}
};




}