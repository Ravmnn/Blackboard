#include <blackboard/rendering/window_renderer.hpp>




void WindowRenderer::begin_render() noexcept
{
    if (use_buffer_texture)
    {
        TextureRenderer::begin_render();
        return;
    }

    BeginDrawing();
    Renderer::begin_render();
}


void WindowRenderer::end_render() noexcept
{
    if (!use_buffer_texture)
    {
        EndDrawing();
        Renderer::end_render();

        return;
    }

    TextureRenderer::end_render();
    render_buffer_to_window();
}


void WindowRenderer::render_buffer_to_window() const noexcept
{
    BeginDrawing();
    clear();

    draw_y_inverted_texture(contents().texture);

    EndDrawing();
}