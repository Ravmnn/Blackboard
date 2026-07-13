#pragma once

#include <cstdint>

#include <initializer_list>
#include <vector>

#include <raylib.h>




namespace bb::editor
{




struct StrokePoint
{
    Vector2 position = {};
    float thickness = 1;
    Color color = WHITE;
    float outline_thickness = 0;
    Color outline_color = WHITE;


    operator Vector2() const noexcept { return position; }
};


class Stroke
{
public:
    std::vector<StrokePoint> points;


    Stroke(const std::initializer_list<StrokePoint>& points) : points(points) {}


    void set_color(const Color& color) noexcept;
    void set_outline_color(const Color& color) noexcept;
    void set_alpha(uint8_t alpha) noexcept;
    void set_outline_alpha(uint8_t alpha) noexcept;
};




}