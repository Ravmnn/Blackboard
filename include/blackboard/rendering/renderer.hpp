#pragma once

#include <raylib.h>

#include <blackboard/activatable.hpp>




class Renderer : Activatable
{
public:
    Color clear_color = BLANK;


    using Activatable::active;


    virtual ~Renderer() = default;


    virtual void begin_render() { enable(); };
    virtual void end_render() { disable(); };


    virtual RenderTexture contents() const noexcept = 0;


    virtual Vector2 resolution() const noexcept
    {
        const RenderTexture render_texture = contents();
        const Vector2 resolution = { render_texture.texture.width, render_texture.texture.height };

        return resolution;
    }
};