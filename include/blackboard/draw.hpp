#pragma once

#include <cstdint>
#include <cstddef>
#include <cmath>

#include <raylib.h>
#include <raymath.h>




namespace bb
{




class Draw
{
private:
    struct CircleSectionTriangle
    {
        Vector2 center;
        Vector2 current;
        Vector2 next;
    };


public:
    static void stretched_ellipse(const Vector2& position, const float radius, const float stretch, const Color& color = WHITE) noexcept {
        DrawEllipse((int)position.x, (int)position.y, radius + stretch, radius,color);
    }


    static void circle_section(const Vector2& center, const float radius, const float start_angle, const float end_angle, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_selection_angle_step(start_angle, end_angle, resolution);

        for (size_t i = 0; i < resolution; i++)
            draw_circle_selection_filled(calculate_circle_selection_triangle(center, radius, start_angle, angle_step, i), color);
    }


    static void circle_section_outline(const Vector2& center, const float radius, const float start_angle, const float end_angle, const float thickness, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_selection_angle_step(start_angle, end_angle, resolution);

        for (size_t i = 0; i < resolution; i++)
            draw_circle_selection_outline(calculate_circle_selection_triangle(center, radius, start_angle, angle_step, i), thickness, color);
    }


private:
    static float calculate_circle_selection_angle_step(const float start_angle, const float end_angle, const uint32_t resolution) noexcept
    {
        const auto angle_distance_in_rads = (float)((end_angle - start_angle) * M_PI / 180.0);
        return angle_distance_in_rads / (float)resolution;
    }


    static CircleSectionTriangle calculate_circle_selection_triangle(const Vector2& center, const float radius, const float start_angle, const float angle_step, const size_t i)
    {
        const auto fi = (float)i;
        const float current_angle = start_angle + fi * angle_step;
        const float next_angle = (float)start_angle + (fi + 1) * angle_step;

        const Vector2 current_point = center + Vector2{ cosf(current_angle) * radius, sinf(current_angle) * radius };
        const Vector2 next_point = center + Vector2{ cosf(next_angle) * radius, sinf(next_angle) * radius };

        return CircleSectionTriangle{ .center = center, .current = current_point, .next = next_point };
    }




    static void draw_circle_selection_filled(const CircleSectionTriangle& triangle, const Color& color) noexcept
    {
        DrawTriangle(triangle.next, triangle.current, triangle.center, color);
    }


    static void draw_circle_selection_outline(const CircleSectionTriangle& triangle, const float thickness, const Color& color) noexcept
    {
        DrawLineEx(
            Vector2MoveTowards(triangle.current, triangle.next, -thickness / 5),
            Vector2MoveTowards(triangle.next, triangle.current, -thickness / 5),
        thickness, color);
    }
};




}