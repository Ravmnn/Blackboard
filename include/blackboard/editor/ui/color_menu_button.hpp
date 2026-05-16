#pragma once

#include <blackboard/ui/components/button.hpp>




class RadialMenu;


class ColorMenuButton final : public Button
{
public:
    static constexpr Vector2 DefaultSize = { 200, 200 };
    static constexpr Vector2 DefaultHoveredSize = { 200, 200 };
    static constexpr float DefaultRadius = DefaultSize.x / 1.5;
    static constexpr float DefaultHoveredRadius = DefaultRadius / 1.3;
    static constexpr float DefaultOutlineThickness = 2;
    static constexpr Color DefaultOutlineColor = { 50, 50, 50, 255 };


    explicit ColorMenuButton(RadialMenu* const parent, const Color& color) noexcept;


protected:
    void on_entered() noexcept override;
    void on_leaved() noexcept override;
};