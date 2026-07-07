#pragma once




namespace bb::editor
{




class Shaders
{
public:

inline static const char* const NegativeStrokeSelection = R"(
#version 330


uniform vec4 u_default_color;
uniform float u_grayness_threshold;


in vec4 fragColor;

out vec4 out_color;


float grayness(vec3 color)
{
    float maxv = max(color.r, max(color.g, color.b));
    float minv = min(color.r, min(color.g, color.b));

    return 1.0 - (maxv - minv);
}


void main()
{
    out_color = 1.0 - fragColor;

    if (grayness(fragColor.rgb) >= u_grayness_threshold)
        out_color = u_default_color;

    out_color.a = 1.0;
}
)";

};




}