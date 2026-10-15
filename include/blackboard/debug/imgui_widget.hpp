#pragma once

#include <string>
#include <string_view>
#include <optional>

#include <imgui.h>

#include <blackboard/debug/format.hpp>




namespace bb::debug
{




class ImGuiWidget
{
public:
    static void begin_window(const std::string& name, const ImVec2& size, bool& is_open, const std::optional<ImVec2>& minimum_size = ImVec2{ 250, 250 }) noexcept;
    static void end_window() noexcept;

    static void begin_frame_child(const std::string& id) noexcept;
    static void end_frame_child() noexcept;


    template <typename T>
    static void text_value(const std::string_view& label, const T& value)
    {
        const std::string formatted = std::format("{}", value);
        ImGui::Text("%.*s: %s", static_cast<int>(label.size()), label.data(), formatted.c_str());
    }


    template <typename T>
    static void optional_text_value(const std::string_view& label, const std::optional<T>& value)
    {
        if (value)
            text_value(label, *value);
    }


    static void selectable_readonly_multi_line_text(const std::string& id, const std::string& text, const ImVec2& size = { -FLT_MIN, -FLT_MIN }) noexcept;


    static void separator(const std::string& title) noexcept;
};




}