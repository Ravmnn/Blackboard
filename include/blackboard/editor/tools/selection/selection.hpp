#pragma once

#include "raylib.h"
#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/selection/body.hpp>




namespace bb::editor
{




class Selection : public Tool
{
private:
    Vector2 start_position_;
    Vector2 end_position_;


public:
    SelectionBody body;


    Selection(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;

    [[nodiscard]] const Vector2& start_position() const noexcept { return start_position_; }
    [[nodiscard]] const Vector2& end_position() const noexcept { return end_position_; }


protected:
    void on_enabled() noexcept override;
};




}