#include <blackboard/editor/editor_background.hpp>

#include <blackboard/animation/interpolate.hpp>
#include <blackboard/math/rect.hpp>
#include <blackboard/editor/editor.hpp>




using
bb::math::Rect,
bb::animation::Interpolate,
bb::rendering::TextureRenderer,
bb::editor::EditorBackground;




EditorBackground::EditorBackground(const Editor& editor, const float zoom_visibility_interval_min, const float zoom_visibility_interval_max) noexcept :
    editor(editor),

    zoom_visibility_interval_min(zoom_visibility_interval_min),
    zoom_visibility_interval_max(zoom_visibility_interval_max)
{
    effect.spacing = 40;
    effect.radius = 0.85;

    effect.alt_spacing = 80;
    effect.alt_radius = 1.0;

    effect.soft_outline_thickness = 0.1;

    max_alpha = 0.3;
}




void EditorBackground::update() noexcept
{
    effect.alt_alpha_factor = get_alpha_factor();
    effect.alpha_factor = effect.alt_alpha_factor * alpha_factor_ratio_;

    update_effect();
}


void EditorBackground::update_effect() noexcept
{
    effect.update();
}


float EditorBackground::get_alpha_factor() const noexcept
{
    const float t = Interpolate::inverse(zoom_visibility_interval_max, zoom_visibility_interval_min, editor.canvas().raylib_camera().zoom);
    return std::clamp(t, min_alpha, max_alpha);
}




void EditorBackground::draw() noexcept
{
    const Vector2 start = editor.canvas().map_point_using_interpolated_camera({ 0, 0 });
    const Vector2 end = editor.canvas().map_point_using_interpolated_camera(editor.canvas().resolution());
    const Rectangle rect = Rect::from_two_points(start, end);

    effect.enable();
    DrawRectangleRec(rect, WHITE);
    effect.disable();
}