#include <blackboard/editor/stroke/stroke.hpp>




using bb::editor::Stroke;




void Stroke::set_color(const Color& color) noexcept
{
    for (auto& point : points)
        point.color = color;
}


void Stroke::set_outline_color(const Color& color) noexcept
{
    for (auto& point : points)
        point.outline_color = color;
}


void Stroke::set_alpha(const uint8_t alpha) noexcept
{
    for (auto& point : points)
        point.color.a = alpha;
}


void Stroke::set_outline_alpha(const uint8_t alpha) noexcept
{
    for (auto& point : points)
        point.outline_color.a = alpha;
}