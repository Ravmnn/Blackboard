#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>




using
bb::rendering::WindowRenderer,
bb::rendering::TextureRenderer,
bb::editor::Canvas;




// TODO: add global antialiasing samples for editor
Canvas::Canvas() noexcept : TextureRenderer(16, true, true),
    camera(*this, 0.2, 8, 0.13)
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