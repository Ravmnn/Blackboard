#pragma once

#include <blackboard/initializable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/editor/effects/dot_pattern.hpp>




namespace bb::editor
{




class Editor;


class EditorBackground : public Updateable, public Drawable
{
private:
    rendering::TextureRenderer texture_;


public:
    const Editor& editor;
    DotPatternEffect effect;


    EditorBackground(const Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_effect() noexcept;
};




}