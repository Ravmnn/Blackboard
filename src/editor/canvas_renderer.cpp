#include <blackboard/editor/canvas_renderer.hpp>

#include <blackboard/rendering/window_renderer.hpp>
#include <blackboard/editor/canvas.hpp>




using bb::editor::CanvasRenderer,
    bb::rendering::WindowRenderer,
    bb::rendering::TextureRenderer;




CanvasRenderer::CanvasRenderer(const Canvas& canvas) noexcept :
    canvas(canvas)
{}




void CanvasRenderer::initialize() noexcept
{
    recreate_texture_renderer();

    Initializable::initialize();
}




void CanvasRenderer::update() noexcept
{
    initialize_if_uninitialized();

    if (IsWindowResized())
        recreate_texture_renderer();

    super_sampled_texture_.clear_color = canvas.background_color();
}


void CanvasRenderer::recreate_texture_renderer() noexcept
{
    const Vector2 screen_resolution = WindowRenderer::screen_resolution();

    super_sampled_texture_ = TextureRenderer(screen_resolution * SuperSamplingFactor, true);
    final_texture_ = TextureRenderer(screen_resolution);
}




void CanvasRenderer::begin_render() noexcept
{
    super_sampled_texture_.begin_render();
}


void CanvasRenderer::end_render() noexcept
{
    super_sampled_texture_.end_render();
    super_sampled_texture_.generate_mipmaps();

    draw_super_sampled_to_final_texture();
}


void CanvasRenderer::draw_contents_texture() noexcept
{
    DrawTextureV(final_texture_.contents().texture, {}, WHITE);
}


void CanvasRenderer::draw_super_sampled_to_final_texture() noexcept
{
    const Texture contents = super_sampled_texture_.contents().texture;
    SetTextureFilter(contents, TEXTURE_FILTER_TRILINEAR);

    const Vector2 source_size = { (float)contents.width, (float)contents.height };
    const Vector2 target_size = final_texture_.resolution();
    const Rectangle source = { 0, 0, source_size.x, source_size.y };
    const Rectangle destination = { 0, 0, target_size.x, target_size.y };

    final_texture_.begin_render();
    DrawTexturePro(contents, source, destination, {}, 0, WHITE);
    final_texture_.end_render();
}