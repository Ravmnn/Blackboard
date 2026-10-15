#include <blackboard/editor/stroke/trail.hpp>

#include <blackboard/camera_matrix.hpp>
#include <blackboard/editor/stroke/stroke_cleaner.hpp>




using bb::editor::Trail;




Trail::Trail(const Camera2D& camera, const StrokePoint& origin, const float decay, const float fraction_decay) noexcept : Stroke({}),
    trail_mesh_generator_(4),
    camera(camera),
    origin(origin),
    decay(decay),
    fraction_decay(fraction_decay)
{}




void Trail::update() noexcept
{
    update_renderer();
    update_points_decayment();

    remove_points_with_no_thickness();

    if (emit)
        points.push_back(origin);
}


void Trail::update_renderer() noexcept
{
    trail_renderer_.effect.mvp = CameraMatrix::get_orthographic_matrix_from_camera(camera);
    trail_renderer_.effect.update();
}


void Trail::update_points_decayment() noexcept
{
    for (auto& point : points)
    {
        if (Vector2Distance(point.position, origin.position) <= 0)
            continue;

        point.thickness -= point.thickness * fraction_decay;
        point.thickness -= decay;
    }
}


void Trail::remove_points_with_no_thickness() noexcept
{
    points.erase(std::remove_if(points.begin(), points.end(),
        [](const auto& point) { return point.thickness <= 0; }
    ), points.end());
}




void Trail::draw() noexcept
{
    const Stroke clean_stroke = StrokeCleaner().clean(*this);
    const std::unique_ptr<StrokeMeshGL> mesh_gl = trail_mesh_generator_.generate_mesh_gl(clean_stroke);

    if (mesh_gl)
        trail_renderer_.draw_stroke_mesh_gl_immediate(*mesh_gl);
}