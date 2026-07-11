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

    float alpha_factor_ratio_ = 1 / 2.0;


public:
    const Editor& editor;
    DotPatternEffect effect;

    float zoom_visibility_interval_min;
    float zoom_visibility_interval_max;
    float max_alpha_factor = 0.6;


    EditorBackground(const Editor& editor, float zoom_visibility_interval_min, float zoom_visibility_interval_max) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_effect() noexcept;

    [[nodiscard]] float get_alpha_factor() const noexcept;
};




}