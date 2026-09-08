#include <blackboard/rendering/effects/shaders.hpp>




using bb::rendering::Shaders;




const char* const Shaders::RoundedRectangleVertex = R"(
#version 330


uniform mat4 mvp;

uniform vec2 u_position;
uniform vec2 u_size;


in vec3 vertexPosition;

out vec2 vertex_local_position;


void main()
{
    vertex_local_position = vertexPosition.xy - u_position;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";




const char* const Shaders::RoundedRectangleFragment = R"(
#version 330


uniform vec2 u_size;
uniform float u_radius;
uniform vec4 u_color;
uniform vec4 u_outline_color;
uniform float u_outline_thickness;
uniform float u_antialiasing;
uniform int u_outline_only;
uniform int u_fill_only;


in vec2 vertex_local_position;
out vec4 out_color;


float sd_rounded_box(vec2 p, vec2 half_size, float radius)
{
    vec2 q = abs(p) - half_size + radius;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - radius;
}


void main()
{
    vec2 half_size = u_size / 2.0;
    float d = sd_rounded_box(vertex_local_position, half_size - u_antialiasing, u_radius);
    float aa = fwidth(d) * u_antialiasing;


    float outer_coverage = 1.0 - smoothstep(0.0, aa, d);

    float d_inner = d + u_outline_thickness;
    float inner_coverage = 1.0 - smoothstep(0.0, aa, d_inner);

    float ring_alpha = clamp(outer_coverage - inner_coverage, 0.0, 1.0);
    float outline_mix = 1.0 - inner_coverage; // 0 = fill, 1 = outline

    vec3 rgb;
    float alpha;

    if (u_outline_only >= 1)
    {
        rgb = u_outline_color.rgb;
        alpha = ring_alpha * u_outline_color.a;
    }
    else if (u_fill_only >= 1)
    {
        rgb = u_color.rgb;
        alpha = inner_coverage * u_color.a;
    }
    else
    {
        rgb = mix(u_color.rgb, u_outline_color.rgb, outline_mix);
        alpha = outer_coverage * mix(u_color.a, u_outline_color.a, outline_mix);
    }

    out_color = vec4(rgb, alpha);

    if (out_color.a <= 0.001)
        discard;
}
)";








const char* const Shaders::EllipseFragment = R"(
#version 330

uniform vec2 u_size;              // largura/altura total da elipse (bounding box)
uniform vec4 u_color;
uniform vec4 u_outline_color;
uniform float u_outline_thickness;
uniform float u_antialiasing;
uniform int u_outline_only;
uniform int u_fill_only;

in vec2 vertex_local_position;
out vec4 out_color;

// Aproximação de distância a uma elipse: exata sobre o contorno (d=0)
// e assintoticamente correta perto dele — suficiente para AA/outline,
// mas NÃO é uma SDF verdadeira longe da borda (não use para raymarching
// ou composição com outras SDFs via min/max).
float sd_ellipse_approx(vec2 p, vec2 ab)
{
    // "distância" no espaço normalizado da elipse (0 dentro, 1 no contorno)
    float k1 = length(p / ab);
    if (k1 == 0.0)
        return -min(ab.x, ab.y);

    // gradiente do campo normalizado, para converter de volta a unidades de mundo
    vec2 grad = p / (ab * ab);
    float k2 = length(grad);

    // (k1 - 1) / k2 aproxima a distância euclidiana real até o contorno
    return (k1 - 1.0) * k1 / max(k2, 1e-6);
}

void main()
{
    vec2 half_size = u_size / 2.0;
    vec2 ab = half_size - u_antialiasing;

    float d = sd_ellipse_approx(vertex_local_position, ab);
    float aa = fwidth(d) * u_antialiasing;

    float outer_coverage = 1.0 - smoothstep(0.0, aa, d);

    float d_inner = d + u_outline_thickness;
    float inner_coverage = 1.0 - smoothstep(0.0, aa, d_inner);

    float ring_alpha = clamp(outer_coverage - inner_coverage, 0.0, 1.0);
    float outline_mix = 1.0 - inner_coverage; // 0 = fill, 1 = outline

    vec3 rgb;
    float alpha;

    if (u_outline_only >= 1)
    {
        rgb = u_outline_color.rgb;
        alpha = ring_alpha * u_outline_color.a;
    }
    else if (u_fill_only >= 1)
    {
        rgb = u_color.rgb;
        alpha = inner_coverage * u_color.a;
    }
    else
    {
        rgb = mix(u_color.rgb, u_outline_color.rgb, outline_mix);
        alpha = outer_coverage * mix(u_color.a, u_outline_color.a, outline_mix);
    }

    out_color = vec4(rgb, alpha);

    if (out_color.a <= 0.001)
        discard;
}
)";