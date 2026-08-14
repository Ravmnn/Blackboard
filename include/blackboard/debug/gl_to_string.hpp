#pragma once

#include <string>

#include <glad.h>




namespace bb::debug
{




class GlToString
{
public:
    static std::string frame_buffer_status(GLenum status) noexcept;
};




}