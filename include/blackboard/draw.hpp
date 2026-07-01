#pragma once

#include <cstdint>
#include <cstddef>
#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include <blackboard/rendering/stencil.hpp>




namespace bb
{




class Draw
{
private:
    struct SectionTriangle
    {
        Vector2 center;
        Vector2 current;
        Vector2 next;
    };


public:
    static void stretched_ellipse(const Vector2& position, const float radius, const float stretch, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        ellipse(position, radius + stretch, radius, color, resolution);
    }


    static void stretched_ellipse_outline(const Vector2& position, const float radius, const float stretch, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        ellipse_outline(position, radius + stretch, radius, thickness, color, resolution);
    }




    static void ellipse(const Vector2& center, const float radius_x, const float radius_y, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        for (size_t i = 0; i < resolution; i++)
            draw_ellipse_filled(calculate_ellipse_section_triangle(center, radius_x, radius_y, resolution, i), color);
    }


    static void ellipse_outline(const Vector2& center, const float radius_x, const float radius_y, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        for (size_t i = 0; i < resolution; i++)
            draw_ellipse_outline(calculate_ellipse_section_triangle(center, radius_x, radius_y, resolution, i), thickness, color);
    }




    static void circle(const Vector2& center, const float radius, const Color& color, const uint32_t resolution = 32) noexcept
    {
        circle_section(center, radius, 0, 360, color, resolution);
    }


    static void circle_outline(const Vector2& center, const float radius, const float thickness, const Color& color, const uint32_t resolution = 32) noexcept
    {
        circle_section_outline(center, radius, 0, 360, thickness, color, resolution);
    }




    static void circle_section(const Vector2& center, const float radius, const float start_angle, const float end_angle, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_section_angle_step(start_angle, end_angle, resolution);

        for (size_t i = 0; i < resolution; i++)
            draw_circle_section_filled(calculate_circle_section_triangle(center, radius, start_angle, angle_step, i), color);
    }


    static void circle_section_outline(const Vector2& center, const float radius, const float start_angle, const float end_angle, const float thickness, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_section_angle_step(start_angle, end_angle, resolution);

        for (size_t i = 0; i < resolution; i++)
            draw_circle_section_outline(calculate_circle_section_triangle(center, radius, start_angle, angle_step, i), thickness, color);
    }


private:
    static SectionTriangle calculate_ellipse_section_triangle(const Vector2& center, const float radius_x, const float radius_y, const uint32_t resolution, const size_t i) noexcept
    {
        const float angle1 = (2.0f * PI * (float)i) / (float)resolution;
        const float angle2 = (2.0f * PI * (float)(i + 1)) / (float)resolution;

        const Vector2 p1 = {
            center.x + cosf(angle1) * radius_x,
            center.y + sinf(angle1) * radius_y
        };

        const Vector2 p2 = {
            center.x + cosf(angle2) * radius_x,
            center.y + sinf(angle2) * radius_y
        };

        return SectionTriangle{ .center = center, .current = p1, .next = p2 };
    }


    static void draw_ellipse_filled(const SectionTriangle& triangle, const Color& color) noexcept
    {
        draw_triangle(triangle, color);
    }


    static void draw_ellipse_outline(const SectionTriangle& triangle, const float thickness, const Color& color) noexcept
    {
        draw_outline(triangle.current, triangle.next, thickness, color);
    }




    static float calculate_circle_section_angle_step(const float start_angle, const float end_angle, const uint32_t resolution) noexcept
    {
        const auto angle_distance_in_rads = (float)((end_angle - start_angle) * M_PI / 180.0);
        return angle_distance_in_rads / (float)resolution;
    }


    static SectionTriangle calculate_circle_section_triangle(const Vector2& center, const float radius, const float start_angle, const float angle_step, const size_t i)
    {
        const auto fi = (float)i;
        const float current_angle = start_angle + fi * angle_step;
        const float next_angle = (float)start_angle + (fi + 1) * angle_step;

        const Vector2 current_point = center + Vector2{ cosf(current_angle) * radius, sinf(current_angle) * radius };
        const Vector2 next_point = center + Vector2{ cosf(next_angle) * radius, sinf(next_angle) * radius };

        return SectionTriangle{ .center = center, .current = current_point, .next = next_point };
    }


    static void draw_circle_section_filled(const SectionTriangle& triangle, const Color& color) noexcept
    {
        draw_triangle(triangle, color);
    }


    static void draw_circle_section_outline(const SectionTriangle& triangle, const float thickness, const Color& color) noexcept
    {
        draw_outline(triangle.current, triangle.next, thickness, color);
    }




    static void draw_triangle(const SectionTriangle& triangle, const Color& color) noexcept
    {
        DrawTriangle(triangle.next, triangle.current, triangle.center, color);
    }


    static void draw_outline(const Vector2& start, const Vector2& end, const float thickness, const Color& color) noexcept
    {
        // TODO: fix alpha problem... maybe use stencil? Stencil::recover() to avoid loss of previous stencil operation
        DrawLineEx(start, end, thickness, color);
        DrawCircleV(end, thickness / 2, color);
    }
};




}