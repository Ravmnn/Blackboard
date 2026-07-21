#pragma once

#include <blackboard/rendering/texture_renderer.hpp>




namespace bb::rendering
{




class WindowRenderer : public TextureRenderer
{
public:
    bool use_buffer_texture = true;


    WindowRenderer() : TextureRenderer(screen_resolution()) { clear_color = BLACK; }


    void begin_render() noexcept override;
    void end_render() noexcept override;


    // TODO: detect window resizing and update buffer texture size

    [[nodiscard]] Vector2 resolution() const noexcept override { return screen_resolution(); }

    static Vector2 screen_resolution() noexcept { return { (float)GetScreenWidth(), (float)GetScreenHeight() }; }


protected:
    void render_buffer_to_window() const noexcept;
};




}