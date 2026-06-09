#pragma once

#include <blackboard/ui/components/button.hpp>




namespace bb::editor
{




class ColorMenu;


class ColorMenuButton final : public ui::Button
{
public:
    static constexpr Vector2 DefaultSize = { 60, 60 };
    static constexpr Vector2 DefaultHoveredSize = { 70, 70 };
    static constexpr float DefaultRadius = DefaultSize.x / 2;
    static constexpr float DefaultOutlineThickness = 2;
    static constexpr Color DefaultOutlineColor = { 50, 50, 50, 255 };

    static constexpr float SpringSpeed = 16;
    static constexpr float SpringDamping = 0.5;

    static constexpr float ColorInterpolationSpeed = 10;


    explicit ColorMenuButton(ColorMenu* parent, const Color& color) noexcept;


protected:
    void on_entered() noexcept override;
    void on_leaved() noexcept override;
};




}