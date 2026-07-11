#include "raylib.h"
#include <blackboard/editor/effects/dot_pattern.hpp>

#include <blackboard/editor/effects/native_shaders.hpp>




using bb::editor::DotPatternEffect;




DotPatternEffect::DotPatternEffect() noexcept :
    rendering::Effect(LoadShaderFromMemory(Shaders::DotPatternVertex, Shaders::DotPatternFragment)),

    spacing(shader(), "u_spacing", 50),
    alt_spacing(shader(), "u_alt_spacing", 0),
    radius(shader(), "u_radius", 1.5),
    alt_radius(shader(), "u_alt_radius", 0),
    alpha_factor(shader(), "u_alpha_factor", 0.8),
    alt_alpha_factor(shader(), "u_alt_alpha_factor", 0),
    soft_outline_thickness(shader(), "u_soft_outline_thickness", 1),
    color(shader(), "u_color", WHITE),
    alt_color(shader(), "u_alt_color", WHITE),
    background_color(shader(), "u_background_color", BLACK)
{
    shader().locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader(), "mvp");
}




void DotPatternEffect::update() noexcept
{
    Effect::update();

    spacing.update();
    radius.update();
    alpha_factor.update();
    alt_spacing.update();
    alt_radius.update();
    alt_alpha_factor.update();
    soft_outline_thickness.update();
    color.update();
    alt_color.update();
    background_color.update();
}