#pragma once

#include <map>
#include <functional>

#include <blackboard/mouse_button_event.hpp>




class Clickable : public virtual Updateable
{
private:
    bool was_hover_ = false;
    bool hover_ = false;

    std::map<int, MouseButtonEvent> mouse_buttons_;


public:
    const MousePositionProvider* mouse_position_provider;

    Event<> entered;
    Event<> leaved;
    Event<> hover;

    bool ignore_input = false;
    bool ignore_event_triggering = false;
    bool caught_mouse_input = false;


    explicit Clickable(const MousePositionProvider* const mouse_position_provider) noexcept;
    virtual ~Clickable() noexcept = default;


    MouseButtonEvent& operator[](const int button) { return mouse_buttons_[button]; }


    void update() noexcept override;


    const std::map<int, MouseButtonEvent>& mouse_buttons() const noexcept { return mouse_buttons_; }

    bool is_down() const noexcept { return all_buttons([](const auto& button) { return button.is_down(); }); }
    bool is_pressed() const noexcept { return all_buttons([](const auto& button) { return button.is_pressed(); }); }
    bool is_released() const noexcept { return all_buttons([](const auto& button) { return button.is_released(); }); }
    bool is_clicked() const noexcept { return all_buttons([](const auto& button) { return button.is_clicked(); }); }

    bool is_hover() const noexcept { return hover_; }

    bool is_mouse_over() const noexcept { return is_point_over(mouse_position_provider->mouse_position()); }
    virtual bool is_point_over(const Vector2& point) const noexcept = 0;

    virtual bool can_receive_input() const noexcept { return !ignore_input; }


    void add_mouse_button_event(const int id) noexcept;


protected:
    void update_interaction() noexcept;
    void update_mouse_buttons() noexcept;


    virtual void on_entered() noexcept {}
    virtual void on_leaved() noexcept {}
    virtual void on_hover() noexcept {}


    using MouseButtonPredicate = std::function<bool (const MouseButtonEvent&)>;

    bool all_buttons(const MouseButtonPredicate& predicate) const noexcept;
};