#pragma once

#include <blackboard/editor/stroke/stroke_mesh.hpp>




namespace bb::editor
{
    class Editor;
}


namespace bb::debug
{




class InspectorImGui
{
public:
    inline static bool is_open = false;
    inline static editor::Editor* editor = nullptr;


    static void draw() noexcept;


private:
    static void draw_inspection() noexcept;
    static void draw_node_highlight(const editor::StrokeMeshNode& node) noexcept;
};




}