#include <blackboard/editor/canvas.hpp>

#include <blackboard/rendering/window_renderer.hpp>




using
bb::rendering::WindowRenderer,
bb::rendering::TextureRenderer,
bb::ui::Clickable,
bb::ui::Component,
bb::editor::Canvas;




// TODO: add global antialiasing samples for editor
Canvas::Canvas(Component* parent) noexcept :
    Component(parent, {}),
    Clickable(*dynamic_cast<MousePositionProvider*>(this)),
    TextureRenderer(16, true, true),

    middle_button(MOUSE_BUTTON_MIDDLE, *this),

    camera(*this, 0.2, 8, 0.13)
{
    clip = false;
    block_input = false;

    camera.bounds_expansion = { 100, 100 };

    clear_color = BLANK;


    add_mouse_button_event(MOUSE_BUTTON_MIDDLE, *this, this);
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

    Clickable::update();
    Component::update();

    camera.update();
}


void Canvas::draw_self() noexcept
{
    draw_y_inverted_texture_full();
}




void Canvas::resize_texture_renderer() noexcept
{
    resize(WindowRenderer::screen_resolution());
}