#pragma once

#include <glad.h>




namespace bb::debug
{




class GlDebug
{
public:
    static void setup_gl_debug(GLDEBUGPROC callback = nullptr) noexcept;


private:
    static void default_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) noexcept;
};




}