#pragma once




namespace bb::editor
{




class Shaders
{
public:

inline static const char* const NegativeStrokeSelection = R"(
#version 330


uniform float u_time;
uniform vec2 u_resolution;

uniform float u_spacing;
uniform float u_speed;
uniform float u_thickness;
uniform float u_smoothness;
uniform vec4 u_color;
uniform vec4 u_background_color;


out vec4 out_color;


void main()
{
    vec2 uv = gl_FragCoord.xy;

    float line = (uv.x - uv.y) + u_time * u_speed;
    float pattern = mod(line, u_spacing);
    pattern = min(pattern, u_spacing - pattern);
    float normalized_dist = smoothstep(u_thickness - u_smoothness, u_thickness, pattern);

    float color_factor = mix(0.0, 1.0, 1 - normalized_dist);

    vec4 final_color = mix(u_background_color, u_color, color_factor);

    out_color = final_color;
}
)";








inline static const char* const DotPatternVertex = R"(
#version 330


in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;


out vec2 worldPos;


void main()
{
    worldPos = vertexPosition.xy;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";




inline static const char* const DotPatternFragment = R"(
#version 330


uniform float u_spacing;
uniform float u_alt_spacing;

uniform float u_radius;
uniform float u_alt_radius;

uniform float u_alpha_factor;
uniform float u_alt_alpha_factor;

uniform float u_soft_outline_thickness;

uniform vec4 u_color;
uniform vec4 u_alt_color;
uniform vec4 u_background_color;


in vec2 worldPos;

out vec4 out_color;


void main()
{
    vec2 uv = worldPos;

    vec2 cell = mod(uv, u_spacing) - u_spacing * 0.5;
    float dist = length(cell);

    vec2 alt_cell = mod(uv, u_alt_spacing) - u_spacing * 0.5;
    float alt_dist = length(alt_cell);

    float alpha = 1.0 - smoothstep(u_radius - u_soft_outline_thickness, u_radius + u_soft_outline_thickness, dist);
    float alt_alpha = 1.0 - smoothstep(u_alt_radius - u_soft_outline_thickness, u_alt_radius + u_soft_outline_thickness, alt_dist);

    alpha *= u_alpha_factor;
    alt_alpha *= u_alt_alpha_factor;

    vec3 final_color = u_background_color.rgb;

    if (alt_alpha > 0.001)
        final_color = mix(u_background_color, u_alt_color, alt_alpha).rgb;

    else if (alpha > 0.001)
        final_color = mix(u_background_color, u_color, alpha).rgb;

    out_color = vec4(final_color, 1.0);
}
)";

};




}