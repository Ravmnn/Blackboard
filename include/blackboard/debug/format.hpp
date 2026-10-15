#pragma once

#include <format>

#include <raylib.h>




template <>
struct std::formatter<Vector2> : std::formatter<float>
{
    template <class FormatContext>
    auto format(const Vector2& v, FormatContext& ctx) const
    {
        auto out = ctx.out();

        *out++ = '(';

        ctx.advance_to(out);
        out = std::formatter<float>::format(v.x, ctx);

        out = std::format_to(out, ", ");

        ctx.advance_to(out);
        out = std::formatter<float>::format(v.y, ctx);

        *out++ = ')';

        return out;
    }
};




template <>
struct std::formatter<Color> : std::formatter<uint8_t>
{
    template <class FormatContext>
    auto format(const Color& color, FormatContext& ctx) const
    {
        auto out = ctx.out();

        *out++ = '(';

        ctx.advance_to(out);
        out = std::formatter<uint8_t>::format(color.r, ctx);

        out = std::format_to(out, ", ");

        ctx.advance_to(out);
        out = std::formatter<uint8_t>::format(color.g, ctx);

        out = std::format_to(out, ", ");

        ctx.advance_to(out);
        out = std::formatter<uint8_t>::format(color.b, ctx);


        *out++ = ')';

        return out;
    }
};