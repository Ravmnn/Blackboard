#pragma once

#include <blackboard/editor/editor_environment.hpp>




namespace bb::editor
{




class EditorSelectionEnvironment : public EditorEnvironment
{
public:
    explicit EditorSelectionEnvironment(Editor& editor) noexcept;
};




}