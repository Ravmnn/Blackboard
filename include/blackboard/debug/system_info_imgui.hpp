#pragma once

namespace bb::debug
{




class SystemInfoImGui
{
public:
    inline static bool is_open = false;


    static void draw() noexcept;


private:
    static void draw_computer() noexcept;
    static void draw_os() noexcept;
    static void draw_mainboard() noexcept;
    static void draw_cpu() noexcept;
    static void draw_gpu() noexcept;
    static void draw_graphics() noexcept;
    static void draw_memory() noexcept;
    static void draw_disks() noexcept;
};




}