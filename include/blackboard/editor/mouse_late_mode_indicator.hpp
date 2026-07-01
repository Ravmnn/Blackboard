#pragma once

#include <blackboard/drawable.hpp>
#include <blackboard/mouse_button_set.hpp>
#include <blackboard/animation/spring.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::editor
{




class MouseLateModeIndicator : public Updateable, public Drawable
{
private:
    Stopwatch mouse_button_late_mode_stopwatch_;
    std::chrono::milliseconds time_to_enter_late_mode_;

    std::optional<int> pressed_button_id_ = std::nullopt;


    animation::Spring<float> ring_radius_;
    animation::ExponentialInterpolation<float> ring_transparency_;

    float entering_late_mode_radius_factor_ = 1.05;
    float entered_late_mode_radius_factor = 1.2;

    float entering_late_mode_final_alpha_ = 0;
    float entered_late_mode_final_alpha_ = 255;


public:
    // TODO: late mode not working fully correctly

    const MousePositionProvider& mouse_provider;
    MouseButtonSet& buttons;

    float base_ring_radius = 19;

    Color color = RED;
    float idle_saturation = 0.3;


    explicit MouseLateModeIndicator(const MousePositionProvider& mouse_provider, MouseButtonSet& buttons) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_appearence() noexcept;
    void base_appearence() noexcept;
    void late_mode_appearence() noexcept;

    void update_animations() noexcept;


    [[nodiscard]] bool has_entered_late_mode() const noexcept { return get_late_mode_entering_progress() >= 1; }
    [[nodiscard]] float get_late_mode_entering_progress() const noexcept { return std::min((float)mouse_button_late_mode_stopwatch_.elapsed_ms().count() / (float)time_to_enter_late_mode_.count(), 1.0f); }

    [[nodiscard]] Color get_ring_color() const noexcept;


    void enter_late_mode(const MouseButtonEvent& button) noexcept;
    void leave_late_mode() noexcept;


    void on_button_press(const MouseButtonEvent& button) noexcept;
    void on_button_release(const MouseButtonEvent& button) noexcept;
    void on_button_drag_start(const MouseButtonEvent& button) noexcept;
};




}