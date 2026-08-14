#include <blackboard/debug/gl_to_string.hpp>




using bb::debug::GlToString;




std::string GlToString::frame_buffer_status(const GLenum status) noexcept
{
    switch (status)
    {
        case GL_FRAMEBUFFER_COMPLETE:                      return "Complete";
        case GL_FRAMEBUFFER_UNDEFINED:                     return "Undefined";
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         return "Incomplete Attachment";
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "Missing Attachment";
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        return "Incomplete Draw Buffer";
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        return "Incomplete Read Buffer";
        case GL_FRAMEBUFFER_UNSUPPORTED:                   return "Unsupported";
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        return "Incomplete Multisample";
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      return "Incomplete Layer Targets";

        case 0:                                            return "Unknown (check glGetError)";
        default:                                           return "Invalid Status";
    }
}