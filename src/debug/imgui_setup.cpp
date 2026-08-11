#include <blackboard/debug/imgui_setup.hpp>

#include <rl_imgui_colors.h>




using bb::debug::IMGUISetup;




void IMGUISetup::setup_style() noexcept
{
    auto& style = ImGui::GetStyle();

    style.FontSizeBase = 17;

    style.Alpha = 0.8;
    style.FrameRounding = 5;
    style.FrameBorderSize = 1;
    style.WindowBorderSize = 2;
    style.WindowRounding = 7;
    style.WindowTitleAlign = { 0.5, 0.5 };

    style.Colors[ImGuiCol_FrameBg] = ThemeColorSofter;
    style.Colors[ImGuiCol_FrameBgHovered] = ThemeColorHoveredSofter;
    style.Colors[ImGuiCol_FrameBgActive] = ThemeColorActiveSofter;

    style.Colors[ImGuiCol_Border] = ThemeColorBorder;
    style.Colors[ImGuiCol_Text] = ThemeColorActive;

    style.Colors[ImGuiCol_Button] = ThemeColor;
    style.Colors[ImGuiCol_ButtonHovered] = ThemeColorHovered;
    style.Colors[ImGuiCol_ButtonActive] = ThemeColorActive;

    style.Colors[ImGuiCol_WindowBg] = ThemeWindowColor;

    style.Colors[ImGuiCol_TitleBg] = ThemeWindowTitleColor;
    style.Colors[ImGuiCol_TitleBgActive] = ThemeWindowTitleColor;
    style.Colors[ImGuiCol_TitleBgCollapsed] = ThemeWindowTitleColor;

    style.Colors[ImGuiCol_ResizeGrip] = ThemeColorHighlight;
    style.Colors[ImGuiCol_ResizeGripHovered] = ThemeColorHighlight;
    style.Colors[ImGuiCol_ResizeGripActive] = ThemeColorHighlight;

    style.Colors[ImGuiCol_Header] = ThemeColorSofter;
    style.Colors[ImGuiCol_HeaderHovered] = ThemeColorHoveredSofter;
    style.Colors[ImGuiCol_HeaderActive] = ThemeColorActiveSofter;
}