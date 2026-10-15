#pragma once

#include <raylib.h>
#include <raymath.h>




namespace bb
{




class MousePositionProvider
{
private:
    static MousePositionProvider* screen_;


public:
    virtual ~MousePositionProvider() = default;


    [[nodiscard]] virtual Vector2 mouse_delta() const noexcept { return GetMouseDelta(); };
    [[nodiscard]] float mouse_speed() const noexcept { return Vector2Length(mouse_delta()); }
    [[nodiscard]] virtual Vector2 mouse_position() const noexcept { return GetMousePosition(); };
    [[nodiscard]] virtual Vector2 screen_mouse_position() const noexcept { return GetMousePosition(); };


    static MousePositionProvider& screen() noexcept { return *screen_; }
};




}