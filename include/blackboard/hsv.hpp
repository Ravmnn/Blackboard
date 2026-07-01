#pragma once

#include <raylib.h>




namespace bb
{




class HSV
{
public:
    static Color apply_saturation(const Color& color, const float saturation) noexcept
    {
        const Vector3 hsv = ColorToHSV(color);
        return ColorFromHSV(hsv.x, saturation, hsv.z);
    }
};




}