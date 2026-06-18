#pragma once

#include <raylib.h>


#include <blackboard/activatable.hpp>
#include <blackboard/rendering/stencil.hpp>




namespace bb::rendering
{




class Renderer : Activatable
{
public:
    Color clear_color = BLANK;


    using Activatable::active;


    virtual void begin_render() { enable(); clear(); }
    virtual void end_render() { disable(); }


    [[nodiscard]] virtual RenderTexture contents() const noexcept = 0;


    [[nodiscard]] virtual Vector2 resolution() const noexcept
    {
        const RenderTexture render_texture = contents();
        const Vector2 resolution = { (float)render_texture.texture.width, (float)render_texture.texture.height };

        return resolution;
    }


protected:
    void clear() const noexcept { ClearBackground(clear_color); Stencil::clear(); }
};




}