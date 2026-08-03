#include <blackboard/rendering/window_renderer.hpp>




using bb::rendering::WindowRenderer;




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
    clear_without_enabling();

    draw_y_inverted_texture_full(contents().texture);

    EndDrawing();
}