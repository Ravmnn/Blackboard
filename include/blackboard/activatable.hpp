#pragma once






namespace bb
{




class Activatable
{
private:
    bool active_ = false;


public:
    virtual ~Activatable() = default;


    virtual void enable() { active_ = true; }
    virtual void disable() { active_ = false; }

    void set_active(const bool active) noexcept { active ? enable() : disable(); }

    [[nodiscard]] bool active() const noexcept { return active_; }
};




}