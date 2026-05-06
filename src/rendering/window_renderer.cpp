#include <blackboard/rendering/window_renderer.hpp>




void WindowRenderer::begin_render() noexcept
{
    if (use_buffer_texture)
    {
        TextureRenderer::begin_render();
        return;
    }

    Renderer::begin_render();

    BeginDrawing();
    ClearBackground(clear_color);
}


void WindowRenderer::end_render() noexcept
{
    if (!use_buffer_texture)
    {
        Renderer::end_render();

        EndDrawing();
        return;
    }

    TextureRenderer::end_render();
    render_buffer_to_window();
}


void WindowRenderer::render_buffer_to_window() const noexcept
{
    BeginDrawing();
    ClearBackground(clear_color);

    draw_y_inverted_texture(contents().texture);

    EndDrawing();
}