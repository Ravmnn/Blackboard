#include <blackboard/debug/gl_debug.hpp>

#include <blackboard/debug/logger.hpp>




using bb::debug::GlDebug;




void GlDebug::setup_gl_debug(const GLDEBUGPROC callback) noexcept
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(callback ? callback : default_debug_callback, nullptr);
}


void GlDebug::default_debug_callback(
    const GLenum source, const GLenum type, const GLuint id, const GLenum severity, const GLsizei length,
    const GLchar* message, const void* userParam
) noexcept
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    if (type == GL_DEBUG_TYPE_ERROR)
        Logger::error(message);
    else
        Logger::info(message);
}