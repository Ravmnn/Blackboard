#pragma once

#include <raylib.h>




class Renderizable
{
public:
    virtual RenderTexture render() = 0;
};