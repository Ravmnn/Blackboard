#pragma once

#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/eraser/body.hpp>




namespace bb::editor
{




class Eraser : public Tool
{
public:
    using Tool::Tool;


    EraserBody body;


    explicit Eraser(Canvas& canvas) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;
};




}