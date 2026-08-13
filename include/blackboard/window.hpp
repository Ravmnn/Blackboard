#pragma once

#include <raylib.h>
#include <raymath.h>




namespace bb
{



class Window
{
private:
    inline static Vector2 last_size_ = {};
    inline static Vector2 last_position_ = {};


public:
    static void refresh() noexcept
    {
        last_size_ = size();
        last_position_ = position();
    }


    static Vector2 position() noexcept { return GetWindowPosition(); }
    static Vector2 size() noexcept { return { (float)GetScreenWidth(), (float)GetScreenHeight() }; }


    static bool resized() noexcept
    {
        const bool has = last_size_ != size();
        refresh();

        return has;
    }

    static bool moved() noexcept
    {
        const bool has = last_position_ != position();
        refresh();

        return has;
    }
};




}