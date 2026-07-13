#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>




using bb::editor::Canvas,
    bb::rendering::WindowRenderer,
    bb::rendering::TextureRenderer;




Canvas::Canvas() noexcept : TextureRenderer(true),
    camera(*this, 0.2, 5, 0.13)
{
    camera.bounds_expansion = { 100, 100 };

    clear_color = BLANK;
}




void Canvas::initialize() noexcept
{
    resize_texture_renderer();

    Initializable::initialize();
}





void Canvas::update() noexcept
{
    initialize_if_uninitialized();

    if (IsWindowResized())
        resize_texture_renderer();

    camera.update();
}


void Canvas::resize_texture_renderer() noexcept
{
    resize(WindowRenderer::screen_resolution());
}