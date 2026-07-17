#include <blackboard/editor/effects/native_shaders.hpp>




using bb::editor::Shaders;




const char* const Shaders::StrokeVertex = R"(
#version 330


uniform mat4 u_mvp;


layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in float vertex_border_distance;


out vec2 position;
out vec4 color;
out float border_distance;


void main()
{
    gl_Position = u_mvp * vec4(vertex_position, 0.0, 1.0);

    position = vertex_position;
    color = vertex_color;
    border_distance = vertex_border_distance;
}
)";




const char* const Shaders::StrokeFragment = R"(
#version 330


uniform float u_camera_zoom;
uniform float u_smoothness;


in vec2 position;
in vec4 color;
in float border_distance;


out vec4 out_color;


void main()
{
    // TODO: clamp smoothness so it doesn't explode when zoom out is too high
    float fade = smoothstep(0.0, u_smoothness / u_camera_zoom, border_distance);

    vec4 final_color = color;
    final_color.a = mix(0, color.a, fade);

    out_color = final_color;
}
)";








const char* const Shaders::StrokeSelectionFragment = R"(
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








const char* const Shaders::DotPatternVertex = R"(
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




const char* const Shaders::DotPatternFragment = R"(
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