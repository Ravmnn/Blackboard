#pragma once

#include <rl_imgui_colors.h>




namespace bb::debug
{




class IMGUISetup
{
public:
    inline static const ImVec4 ThemeColorText = rlImGuiColors::Convert(Color(255, 200, 200, 255));
    inline static const ImVec4 ThemeColorBorder = rlImGuiColors::Convert(Color(150, 30, 10, 255));

    inline static const ImVec4 ThemeColor = rlImGuiColors::Convert(Color(230, 50, 20, 255));
    inline static const ImVec4 ThemeColorHovered = rlImGuiColors::Convert(Color(240, 160, 150, 255));
    inline static const ImVec4 ThemeColorActive = rlImGuiColors::Convert(Color(240, 180, 190, 255));
    inline static const ImVec4 ThemeColorHighlight = rlImGuiColors::Convert(Color(255, 50, 50, 255));

    inline static const ImVec4 ThemeWindowColor = rlImGuiColors::Convert(Color(30, 10, 10, 200));
    inline static const ImVec4 ThemeWindowTitleColor = rlImGuiColors::Convert(Color(50, 10, 10, 200));


    static void setup_style() noexcept;
};




}