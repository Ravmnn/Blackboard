#include <blackboard/editor/palette.hpp>




using bb::editor::Palette;




Palette::Palette(const Color& current_color) noexcept :
    current_color_(current_color),
    last_color_(background_color_from_current())
{}




Color Palette::background_color_from_current() const noexcept
{
    const Vector3 hsv = ColorToHSV(current_color_);
    const Color color = ColorFromHSV(hsv.x, hsv.y, hsv.z / 20.0f);

    return color;
}




void Palette::set_current_color(const Color& color) noexcept
{
    last_color_ = current_color_;
    current_color_ = color;
}