#pragma once

#include <raylib.h>






namespace bb::editor
{




class Palette
{
private:
    Color current_color_;
    Color last_color_;


public:
    explicit Palette(const Color& current_color) noexcept;


    [[nodiscard]] const Color& current_color() const noexcept { return current_color_; }
    [[nodiscard]] const Color& last_color() const noexcept { return last_color_; }

    [[nodiscard]] Color background_color_from_current() const noexcept;


    void set_current_color(const Color& color) noexcept;

    void switch_to_last() noexcept { set_current_color(last_color_); }
};




}