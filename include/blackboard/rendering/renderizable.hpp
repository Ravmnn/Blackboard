#pragma once

#include <raylib.h>






namespace bb::rendering
{




class Renderizable
{
public:
    virtual RenderTexture render() = 0;
};




}