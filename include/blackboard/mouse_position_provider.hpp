#pragma once

#include <raylib.h>




class MousePositionProvider
{
public:
    virtual ~MousePositionProvider() = default;

    virtual Vector2 mouse_delta() const noexcept { return GetMouseDelta(); };
    virtual Vector2 mouse_position() const noexcept { return GetMousePosition(); };
    virtual Vector2 screen_mouse_position() const noexcept { return GetMousePosition(); };
};