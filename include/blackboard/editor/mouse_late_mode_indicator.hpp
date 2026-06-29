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

    float entering_late_mode_radius_factor_ = 1.15;
    float entered_late_mode_radius_factor = 1.4;


public:
    const MousePositionProvider& mouse_provider;
    MouseButtonSet& buttons;

    float base_ring_radius = 20;


    explicit MouseLateModeIndicator(const MousePositionProvider& mouse_provider, MouseButtonSet& buttons) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_animations() noexcept;


    [[nodiscard]] float get_stopwatch_progress() const noexcept { return std::min((float)mouse_button_late_mode_stopwatch_.elapsed_ms().count() / (float)time_to_enter_late_mode_.count(), 1.0f); }
    [[nodiscard]] bool stopwatch_finished() const noexcept { return get_stopwatch_progress() >= 1; }

    [[nodiscard]] Color get_ring_color() const noexcept { return ColorAlpha(stopwatch_finished() ? RED : WHITE, ring_transparency_ / 255); }


    void on_button_press(const MouseButtonEvent& button) noexcept;
    void on_button_release(const MouseButtonEvent& button) noexcept;
};




}