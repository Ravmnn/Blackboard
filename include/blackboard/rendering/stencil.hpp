#pragma once

#include <glad.h>

#include <blackboard/rendering/rlgl.hpp>




namespace bb::rendering
{




class Stencil
{
public:
    static void enable() noexcept { flush(); glEnable(GL_STENCIL_TEST); }
    static void disable() noexcept { flush(); glDisable(GL_STENCIL_TEST); }

    static void clear() noexcept
    {
        flush();

        glStencilMask(0xFF);
        glClearStencil(0);
        glClear(GL_STENCIL_BUFFER_BIT);
    }


    static void enable_color() noexcept { glColorMask(true, true, true, true); }
    static void disable_color() noexcept { glColorMask(false, false, false, false); }


    static void begin_write(const int condition, const int stencil_value, const GLenum stencil_op) noexcept
    {
        set(condition, stencil_value, stencil_op);
    }


    static void begin_mask(const int condition, const int stencil_value) noexcept
    {
        set(condition, stencil_value, GL_KEEP, true);
    }


    static void set(const int condition, const int stencil_value, const GLenum stencil_op, const bool read_only = false) noexcept
    {
        flush();

        glStencilFunc(condition, stencil_value, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, stencil_op);
        glStencilMask(read_only ? 0x00 : 0xFF);
    }


private:
    static void flush() noexcept { RLGL::draw_render_batch_active(); }
};




}