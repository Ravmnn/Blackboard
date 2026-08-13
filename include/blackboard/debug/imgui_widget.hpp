#pragma once

#include <string>
#include <optional>

#include <imgui.h>




namespace bb::debug
{




class ImGuiWidget
{
public:
    static void begin_window(const std::string& name, const ImVec2& size, bool& is_open, const std::optional<ImVec2>& minimum_size = std::nullopt) noexcept;
    static void end_window() noexcept;

    static void begin_frame_child(const std::string& id) noexcept;
    static void end_frame_child() noexcept;


    static void selectable_readonly_multi_line_text(const std::string& id, const std::string& text, const ImVec2& size = { -FLT_MIN, -FLT_MIN }) noexcept;
};




}