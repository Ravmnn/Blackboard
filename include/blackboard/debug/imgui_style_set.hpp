#pragma once

#include <rl_imgui_colors.h>




namespace bb::debug
{




class ImGuiStyleSet
{
public:
    inline static const ImVec4 ThemeColor = rlImGuiColors::Convert(Color(215, 50, 20, 255));
    inline static const ImVec4 ThemeColorHovered = rlImGuiColors::Convert(Color(220, 90, 90, 255));
    inline static const ImVec4 ThemeColorActive = rlImGuiColors::Convert(Color(240, 120, 120, 255));
    inline static const ImVec4 ThemeColorHighlight = rlImGuiColors::Convert(Color(255, 50, 50, 255));

    inline static const ImVec4 ThemeColorSofter = rlImGuiColors::Convert(Color(100, 15, 5, 255));
    inline static const ImVec4 ThemeColorHoveredSofter = rlImGuiColors::Convert(Color(120, 20, 20, 255));
    inline static const ImVec4 ThemeColorActiveSofter = rlImGuiColors::Convert(Color(140, 30, 30, 255));
    inline static const ImVec4 ThemeColorHighlightSofter = rlImGuiColors::Convert(Color(160, 10, 10, 255));




    inline static const ImVec4 ThemeColorTranslucidBackground = rlImGuiColors::Convert(Color(0, 0, 0, 80));

    inline static const ImVec4 ThemeColorBorder = rlImGuiColors::Convert(Color(150, 30, 10, 255));

    inline static const ImVec4 ThemeWindowColor = rlImGuiColors::Convert(Color(30, 10, 10, 200));
    inline static const ImVec4 ThemeWindowTitleColor = rlImGuiColors::Convert(Color(50, 10, 10, 200));

    inline static const ImVec4 ThemeColorText = rlImGuiColors::Convert(Color(255, 175, 175, 255));

    inline static const ImVec4 ThemeButtonColor = ThemeColorSofter;
    inline static const ImVec4 ThemeButtonColorHovered = ThemeColorHoveredSofter;
    inline static const ImVec4 ThemeButtonColorActive = ThemeColorActiveSofter;

    inline static const ImVec4 ThemeColorScrollBar = ThemeColor;
    inline static const ImVec4 ThemeColorHoveredScrollBar = ThemeColorHovered;
    inline static const ImVec4 ThemeColorActiveScrollBar = ThemeColorActive;


    static void setup_style() noexcept;


    static void push_frame_translucid_background() noexcept;
};




}