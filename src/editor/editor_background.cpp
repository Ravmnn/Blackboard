#include <blackboard/editor/editor_background.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorBackground,
    bb::rendering::TextureRenderer;




EditorBackground::EditorBackground(const Editor& editor) noexcept :
    editor(editor)
{
    effect.spacing = 50;
    effect.radius = 1;
    effect.alpha_factor = 0.15;

    effect.alt_spacing = 100;
    effect.alt_radius = 1.2;
    effect.alt_alpha_factor = 0.25;

    effect.soft_outline_thickness = 0.1;
}




void EditorBackground::update() noexcept
{
    update_effect();
}


void EditorBackground::update_effect() noexcept
{
    effect.resolution = texture_.resolution();
    effect.update();
}




void EditorBackground::draw() noexcept
{
    effect.enable();
    DrawRectangleV({ -8000, -8000 }, { 16000, 16000 }, WHITE);
    effect.disable();
}