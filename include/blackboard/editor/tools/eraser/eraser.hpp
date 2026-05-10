#pragma once

#include <blackboard/editor/tools/tool.hpp>




class Eraser : public Tool
{
public:
    using Tool::Tool;


    void update() noexcept override;
    void draw() noexcept override;
};