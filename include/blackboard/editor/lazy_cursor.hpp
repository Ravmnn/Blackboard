#pragma once

#include <algorithm>

#include <raymath.h>

#include <blackboard/updateable.hpp>
#include <blackboard/initializable.hpp>




namespace bb::editor
{




class Brush;


class LazyCursor : public Updateable, public Initializable
{
private:
    Vector2 last_position_ = {};
    Vector2 current_position_ = {};

    float max_speed_ = 70;

    float smooth_speed_ = 0;


public:
    Vector2 target_position;
    float laziness;

    float speed_smoothing = 0.05;
    float max_smooth_speed = 25;

    bool immediate = false;


    explicit LazyCursor(float laziness) noexcept;


    void initialize() noexcept override;
    void update() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept { return current_position_; }
    [[nodiscard]] Vector2 velocity() const noexcept { return current_position_ - last_position_; }
    [[nodiscard]] float speed() const noexcept { return Vector2Length(velocity()); }
    [[nodiscard]] float smooth_speed() const noexcept { return smooth_speed_; }
    [[nodiscard]] float smooth_speed_fraction() const noexcept { return std::clamp(smooth_speed_ / max_smooth_speed, 0.0f, 1.0f); }

    [[nodiscard]] bool is_too_slow() const noexcept { return current_speed() < 1; };


private:
    void update_position() noexcept;
    void update_smooth_velocity() noexcept;

    [[nodiscard]] float current_speed() const noexcept { return std::min(speed(), max_speed_); }
};




}