#include <blackboard/editor/effects/stroke.hpp>




using bb::editor::StrokeEffect;




StrokeEffect::StrokeEffect() noexcept :
    rendering::Effect(LoadShaderFromMemory(Shaders::StrokeVertex, Shaders::StrokeFragment)),

    mvp(shader(), "u_mvp", {}),
    camera_zoom(shader(), "u_camera_zoom", {}),
    smoothness(shader(), "u_smoothness", 0.1),
    smoothness_min(shader(), "u_smoothness_min", 0.0),
    smoothness_max(shader(), "u_smoothness_max", 0.9),
    smoothness_thickness_influence(shader(), "u_smoothness_thickness_influence", 10)
{
    use_raylib_batch_system = false;
}




void StrokeEffect::update() noexcept
{
    Effect::update();

    mvp.update();
    camera_zoom.update();
    smoothness.update();
    smoothness_min.update();
    smoothness_max.update();
    smoothness_thickness_influence.update();
}