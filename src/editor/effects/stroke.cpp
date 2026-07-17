#include <blackboard/editor/effects/stroke.hpp>




using bb::editor::StrokeEffect;




StrokeEffect::StrokeEffect() noexcept :
    rendering::Effect(LoadShaderFromMemory(Shaders::StrokeVertex, Shaders::StrokeFragment)),

    mvp(shader(), "u_mvp", {}),
    camera_zoom(shader(), "u_camera_zoom", {}),
    smoothness(shader(), "u_smoothness", 0.1)
{
    use_raylib_batch_system = false;
}




void StrokeEffect::update() noexcept
{
    Effect::update();

    mvp.update();
    camera_zoom.update();
    smoothness.update();
}