#pragma once

#include <raylib.h>






namespace bb
{




class MousePositionProvider
{
public:
    virtual ~MousePositionProvider() = default;

    [[nodiscard]] virtual Vector2 mouse_delta() const noexcept { return GetMouseDelta(); };
    [[nodiscard]] virtual Vector2 mouse_position() const noexcept { return GetMousePosition(); };
    [[nodiscard]] virtual Vector2 screen_mouse_position() const noexcept { return GetMousePosition(); };
};




}