#pragma once

#include <map>
#include <functional>

#include <blackboard/mouse_button_event.hpp>




namespace bb::ui
{




class Clickable : public virtual Updateable
{
private:
    bool was_hover_ = false;
    bool hover_ = false;


protected:
    std::map<int, MouseButtonEvent> mouse_buttons_;


public:
    const MousePositionProvider* mouse_position_provider;

    Event<> entered;
    Event<> leaved;
    Event<> hover;

    bool ignore_input = false;
    bool ignore_event_triggering = false;
    bool caught_mouse_input = false;


    explicit Clickable(const MousePositionProvider* mouse_position_provider) noexcept;


    MouseButtonEvent& operator[](const int button) { return mouse_buttons_[button]; }


    void update() noexcept override;


    [[nodiscard]] const std::map<int, MouseButtonEvent>& mouse_buttons() const noexcept { return mouse_buttons_; }

    [[nodiscard]] bool is_down() const noexcept { return any_buttons([](const auto& button) { return button.is_down(); }); }
    [[nodiscard]] bool is_pressed() const noexcept { return any_buttons([](const auto& button) { return button.is_pressed(); }); }
    [[nodiscard]] bool is_released() const noexcept { return any_buttons([](const auto& button) { return button.is_released(); }); }
    [[nodiscard]] bool is_clicked() const noexcept { return any_buttons([](const auto& button) { return button.is_clicked(); }); }

    [[nodiscard]] bool is_hover() const noexcept { return hover_; }

    [[nodiscard]] bool is_mouse_over() const noexcept { return is_point_over(mouse_position_provider->mouse_position()); }
    [[nodiscard]] virtual bool is_point_over(const Vector2& point) const noexcept = 0;

    [[nodiscard]] virtual bool can_receive_input() const noexcept { return !ignore_input; }


    void add_mouse_button_event(int id) noexcept;
    void add_mouse_button_event(const MouseButtonEvent& button) noexcept { mouse_buttons_.insert({ button.button_id, button }); }


protected:
    void update_interaction() noexcept;
    void update_mouse_buttons() noexcept;


    virtual void on_entered() noexcept {}
    virtual void on_leaved() noexcept {}
    virtual void on_hover() noexcept {}


    using MouseButtonPredicate = std::function<bool (const MouseButtonEvent&)>;

    [[nodiscard]] bool any_buttons(const MouseButtonPredicate& predicate) const noexcept;
};




}