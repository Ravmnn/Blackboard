#include <blackboard/rendering/effects/shaders.hpp>




using bb::rendering::Shaders;




const char* const Shaders::RoundedRectangle = R"(
#version 330


uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_radius;
uniform vec4 u_color;
uniform vec4 u_outline_color;
uniform float u_outline_thickness;
uniform float u_antialiasing;


out vec4 out_color;


float sd_rounded_box(vec2 p, vec2 half_size, float radius)
{
    vec2 q = abs(p) - half_size + radius;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - radius;
}


void main()
{
    float d = sd_rounded_box(gl_FragCoord.xy - u_position, u_size / 2, u_radius);
    float aa = fwidth(d) * u_antialiasing;

    float shape_alpha = 1.0 - smoothstep(0.0, aa, d);

    float d_inside = min(d, 0.0);
    float outline_alpha = smoothstep(-u_outline_thickness - aa, -u_outline_thickness, d_inside);
    outline_alpha *= step(0.001, u_outline_thickness);

    vec3 color = mix(u_color, u_outline_color, outline_alpha).rgb;
    out_color = vec4(color, shape_alpha);
}
)";